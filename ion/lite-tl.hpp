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

#include "ion-types.h"
#include "auto/tl/lite_api.h"

namespace ion {

inline tl_object_ptr<lite_api::ionNode_blockIdExt> create_tl_lite_block_id(const BlockIdExt &block_id) {
  return create_tl_object<lite_api::ionNode_blockIdExt>(block_id.id.workchain, block_id.id.shard, block_id.id.seqno,
                                                        block_id.root_hash, block_id.file_hash);
}

inline BlockIdExt create_block_id(const tl_object_ptr<lite_api::ionNode_blockIdExt> &B) {
  return BlockIdExt{B->workchain_, static_cast<td::uint64>(B->shard_), static_cast<BlockSeqno>(B->seqno_),
                    B->root_hash_, B->file_hash_};
}

inline tl_object_ptr<lite_api::ionNode_blockId> create_tl_lite_block_id_simple(const BlockId &block_id) {
  return create_tl_object<lite_api::ionNode_blockId>(block_id.workchain, block_id.shard, block_id.seqno);
}

inline BlockId create_block_id_simple(const tl_object_ptr<lite_api::ionNode_blockId> &B) {
  return BlockId{B->workchain_, static_cast<td::uint64>(B->shard_), static_cast<BlockSeqno>(B->seqno_)};
}

inline BlockIdExt lite_empty_block_id() {
  return BlockIdExt{workchainIdNotYet, 0, 0, RootHash::zero(), FileHash::zero()};
}

inline tl_object_ptr<lite_api::ionNode_zeroStateIdExt> create_tl_lite_zero_state_id(const ZeroStateIdExt &id) {
  return create_tl_object<lite_api::ionNode_zeroStateIdExt>(id.workchain, id.root_hash, id.file_hash);
}

inline ZeroStateIdExt create_zero_state_id(tl_object_ptr<lite_api::ionNode_zeroStateIdExt> &B) {
  return ZeroStateIdExt{B->workchain_, B->root_hash_, B->file_hash_};
}

}  // namespace ion
