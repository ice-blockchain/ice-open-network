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

#include "adnl-peer-table.h"

namespace ion {

namespace adnl {

class AdnlExtServerCreator {
 public:
  static td::actor::ActorOwn<AdnlExtServer> create(td::actor::ActorId<AdnlPeerTable> adnl,
                                                   std::vector<AdnlNodeIdShort> ids, std::vector<td::uint16> ports);
};

}  // namespace adnl

}  // namespace ion
