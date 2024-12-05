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

#include "tl_core.h"
#include "tl_simple_parser.h"

#include <cstddef>
#include <cstdint>
#include <map>
#include <string>
#include <vector>

namespace td {
namespace tl {

class tl_config {
  std::vector<tl_type *> types;
  std::map<std::int32_t, tl_type *> id_to_type;
  std::map<std::string, tl_type *> name_to_type;

  std::vector<tl_combinator *> functions;
  std::map<std::int32_t, tl_combinator *> id_to_function;
  std::map<std::string, tl_combinator *> name_to_function;

 public:
  void add_type(tl_type *type);

  tl_type *get_type(std::int32_t type_id) const;

  tl_type *get_type(const std::string &type_name);

  void add_function(tl_combinator *function);

  tl_combinator *get_function(std::int32_t function_id);

  tl_combinator *get_function(const std::string &function_name);

  std::size_t get_type_count() const;

  tl_type *get_type_by_num(std::size_t num) const;

  std::size_t get_function_count() const;

  tl_combinator *get_function_by_num(std::size_t num) const;
};

class tl_config_parser {
  tl_simple_parser p;
  int schema_version;
  tl_config config;

  static int get_schema_version(std::int32_t version_id);

  tl_tree *read_num_const();
  tl_tree *read_num_var(int *var_count);
  tl_tree *read_type_var(int *var_count);
  tl_tree *read_array(int *var_count);
  tl_tree *read_type(int *var_count);
  tl_tree *read_type_expr(int *var_count);
  tl_tree *read_nat_expr(int *var_count);
  tl_tree *read_expr(int *var_count);
  std::vector<arg> read_args_list(int *var_count);

  tl_combinator *read_combinator();
  tl_type *read_type();

  template <class T>
  T try_parse(const T &res) const;

  std::int32_t try_parse_int();
  std::int64_t try_parse_long();
  std::string try_parse_string();

 public:
  tl_config_parser(const char *s, std::size_t len) : p(s, len), schema_version(-1) {
  }

  tl_config parse_config();
};

}  // namespace tl
}  // namespace td
