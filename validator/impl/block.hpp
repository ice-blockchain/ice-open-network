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
#include "ion/ion-types.h"
#include "interfaces/block.h"
#include "vm/db/StaticBagOfCellsDb.h"

namespace ion {

namespace validator {

class BlockQ : public BlockData {
 private:
  td::BufferSlice data_;
  BlockIdExt id_;
  td::Ref<vm::Cell> root_;
  std::shared_ptr<vm::StaticBagOfCellsDb> boc_;
  //
  BlockQ(const BlockQ& other);
  td::Status init();

 public:
  BlockQ(BlockIdExt id, td::BufferSlice data);
  BlockQ(BlockQ&& other) = default;
  ~BlockQ() override;
  td::BufferSlice data() const override {
    return data_.clone();
  }
  FileHash file_hash() const override {
    return id_.file_hash;
  }
  BlockIdExt block_id() const override {
    return id_;
  }
  td::Ref<vm::Cell> root_cell() const override {
    return root_;
  }
  BlockQ* make_copy() const override {
    return new BlockQ(*this);
  }
  static td::Result<td::Ref<BlockQ>> create(BlockIdExt id, td::BufferSlice data);
};

}  // namespace validator

}  // namespace ion
