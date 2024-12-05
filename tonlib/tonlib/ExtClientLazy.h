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
#pragma once
#include "td/actor/actor.h"

#include "adnl/adnl-ext-client.h"

namespace tonlib {
class ExtClientLazy : public ion::adnl::AdnlExtClient {
 public:
  class Callback {
   public:
    virtual ~Callback() {
    }
  };

  virtual void force_change_liteserver() = 0;

  static td::actor::ActorOwn<ExtClientLazy> create(ion::adnl::AdnlNodeIdFull dst, td::IPAddress dst_addr,
                                                   td::unique_ptr<Callback> callback);
  static td::actor::ActorOwn<ExtClientLazy> create(
      std::vector<std::pair<ion::adnl::AdnlNodeIdFull, td::IPAddress>> servers, td::unique_ptr<Callback> callback);
};

}  // namespace tonlib
