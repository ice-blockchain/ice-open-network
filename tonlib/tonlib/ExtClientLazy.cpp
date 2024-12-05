/*
    This file is part of ION Blockchain Library.

    ION Blockchain Library is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 2 of the License, or
    (at your option) any later version.

    ION Blockchain Library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with ION Blockchain Library.  If not, see <http://www.gnu.org/licenses/>.

    Copyright 2017-2020 Telegram Systems LLP
*/
#include "ExtClientLazy.h"
#include "TonlibError.h"
#include "td/utils/Random.h"
namespace tonlib {

class ExtClientLazyImp : public ExtClientLazy {
 public:
  ExtClientLazyImp(std::vector<std::pair<ion::adnl::AdnlNodeIdFull, td::IPAddress>> servers,
                   td::unique_ptr<ExtClientLazy::Callback> callback)
      : servers_(std::move(servers)), callback_(std::move(callback)) {
    CHECK(!servers_.empty());
  }

  void start_up() override {
    td::Random::Fast rnd;
    td::random_shuffle(td::as_mutable_span(servers_), rnd);
  }

  void check_ready(td::Promise<td::Unit> promise) override {
    before_query();
    if (client_.empty()) {
      return promise.set_error(TonlibError::Cancelled());
    }
    send_closure(client_, &ion::adnl::AdnlExtClient::check_ready, std::move(promise));
  }

  void send_query(std::string name, td::BufferSlice data, td::Timestamp timeout,
                  td::Promise<td::BufferSlice> promise) override {
    before_query();
    if (client_.empty()) {
      return promise.set_error(TonlibError::Cancelled());
    }
    td::Promise<td::BufferSlice> P = [SelfId = actor_id(this), idx = cur_server_idx_,
                                      promise = std::move(promise)](td::Result<td::BufferSlice> R) mutable {
      if (R.is_error() &&
          (R.error().code() == ion::ErrorCode::timeout || R.error().code() == ion::ErrorCode::cancelled)) {
        td::actor::send_closure(SelfId, &ExtClientLazyImp::set_server_bad, idx, true);
      }
      promise.set_result(std::move(R));
    };
    send_closure(client_, &ion::adnl::AdnlExtClient::send_query, std::move(name), std::move(data), timeout,
                 std::move(P));
  }

  void force_change_liteserver() override {
    if (servers_.size() == 1) {
      return;
    }
    cur_server_bad_ = cur_server_bad_force_ = true;
  }

 private:
  void before_query() {
    if (is_closing_) {
      return;
    }
    alarm_timestamp() = td::Timestamp::in(MAX_NO_QUERIES_TIMEOUT);
    if (cur_server_bad_) {
      ++cur_server_idx_;
    } else if (!client_.empty()) {
      return;
    }
    class Callback : public ion::adnl::AdnlExtClient::Callback {
     public:
      explicit Callback(td::actor::ActorShared<ExtClientLazyImp> parent, size_t idx)
          : parent_(std::move(parent)), idx_(idx) {
      }
      void on_ready() override {
        td::actor::send_closure(parent_, &ExtClientLazyImp::set_server_bad, idx_, false);
      }
      void on_stop_ready() override {
        td::actor::send_closure(parent_, &ExtClientLazyImp::set_server_bad, idx_, true);
      }

     private:
      td::actor::ActorShared<ExtClientLazyImp> parent_;
      size_t idx_;
    };
    ref_cnt_++;
    cur_server_bad_ = false;
    cur_server_bad_force_ = false;
    const auto& s = servers_[cur_server_idx_ % servers_.size()];
    LOG(INFO) << "Connecting to liteserver " << s.second;
    client_ = ion::adnl::AdnlExtClient::create(
        s.first, s.second, std::make_unique<Callback>(td::actor::actor_shared(this), cur_server_idx_));
  }

  std::vector<std::pair<ion::adnl::AdnlNodeIdFull, td::IPAddress>> servers_;
  size_t cur_server_idx_ = 0;
  bool cur_server_bad_ = false;
  bool cur_server_bad_force_ = false;

  td::actor::ActorOwn<ion::adnl::AdnlExtClient> client_;
  td::unique_ptr<ExtClientLazy::Callback> callback_;
  static constexpr double MAX_NO_QUERIES_TIMEOUT = 100;

  bool is_closing_{false};
  td::uint32 ref_cnt_{1};

  void set_server_bad(size_t idx, bool bad) {
    if (idx == cur_server_idx_ && servers_.size() > 1 && !cur_server_bad_force_) {
      cur_server_bad_ = bad;
    }
  }
  void alarm() override {
    client_.reset();
  }
  void hangup_shared() override {
    ref_cnt_--;
    try_stop();
  }
  void hangup() override {
    is_closing_ = true;
    ref_cnt_--;
    client_.reset();
    try_stop();
  }
  void try_stop() {
    if (is_closing_ && ref_cnt_ == 0) {
      stop();
    }
  }
};

td::actor::ActorOwn<ExtClientLazy> ExtClientLazy::create(ion::adnl::AdnlNodeIdFull dst, td::IPAddress dst_addr,
                                                         td::unique_ptr<Callback> callback) {
  return create({std::make_pair(dst, dst_addr)}, std::move(callback));
}

td::actor::ActorOwn<ExtClientLazy> ExtClientLazy::create(
    std::vector<std::pair<ion::adnl::AdnlNodeIdFull, td::IPAddress>> servers, td::unique_ptr<Callback> callback) {
  return td::actor::create_actor<ExtClientLazyImp>("ExtClientLazy", std::move(servers), std::move(callback));
}
}  // namespace tonlib
