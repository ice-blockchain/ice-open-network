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
*/
#include "compiler-state.h"
#include <iostream>
#include <sstream>

namespace tolk {

CompilerState G; // the only mutable global variable in tolk internals

void ExperimentalOption::mark_deprecated(const char* deprecated_from_v, const char* deprecated_reason) {
  this->deprecated_from_v = deprecated_from_v;
  this->deprecated_reason = deprecated_reason;
}

void CompilerSettings::enable_experimental_option(std::string_view name) {
  ExperimentalOption* to_enable = nullptr;

  if (name == remove_unused_functions.name) {
    to_enable = &remove_unused_functions;
  }

  if (to_enable == nullptr) {
    std::cerr << "unknown experimental option: " << name << std::endl;
  } else if (to_enable->deprecated_from_v) {
    std::cerr << "experimental option " << name << " "
              << "is deprecated since Tolk v" << to_enable->deprecated_from_v
              << ": " << to_enable->deprecated_reason << std::endl;
  } else {
    to_enable->enabled = true;
  }
}

void CompilerSettings::parse_experimental_options_cmd_arg(const std::string& cmd_arg) {
  std::istringstream stream(cmd_arg);
  std::string token;
  while (std::getline(stream, token, ',')) {
    enable_experimental_option(token);
  }
}

} // namespace tolk
