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

#include "td/utils/int_types.h"

namespace ion {
namespace rldp2 {
// Helper for receiver
// Also this information is sent to the sender as an acknowlegement.
struct Ack {
  td::uint32 max_seqno{0};
  td::uint32 received_mask{0};
  td::uint32 received_count{0};

  // returns true if we know that packet is new and hasn't been received yet
  bool on_got_packet(td::uint32 seqno);
};
}  // namespace rldp2
}  // namespace ion
