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
#include "td/fec/common/SymbolRef.h"
#include "td/utils/Span.h"

namespace td {
namespace raptorq {
class SymbolsView {
 public:
  SymbolsView(size_t symbols_count, size_t symbol_size, Slice data);
  SymbolsView(const SymbolsView &) = delete;
  SymbolsView(SymbolsView &&) = delete;

  Span<SymbolRef> symbols() const {
    return symbols_;
  }

 private:
  std::vector<SymbolRef> symbols_;
  std::string zero_symbol_;
  std::string last_symbol_;
};
}  // namespace raptorq
}  // namespace td
