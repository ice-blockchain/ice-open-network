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
#include "td/utils/Slice.h"

namespace ion {

template <typename T>
typename std::enable_if_t<std::is_integral<T>::value, td::MutableSlice> store_int_to_slice(td::MutableSlice S,
                                                                                           const T &v) {
  CHECK(S.size() >= sizeof(T));
  S.copy_from(td::Slice(reinterpret_cast<const td::uint8 *>(&v), sizeof(T)));
  return S.remove_prefix(sizeof(T));
}

template <typename T>
typename std::enable_if_t<std::is_integral<T>::value, T> fetch_int_from_slice(td::Slice S) {
  CHECK(S.size() >= sizeof(T));
  T v;
  td::MutableSlice(reinterpret_cast<td::uint8 *>(&v), sizeof(T)).copy_from(S.truncate(sizeof(T)));
  return v;
}

}  // namespace ion
