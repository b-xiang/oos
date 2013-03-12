/*
 * This file is part of OpenObjectStore OOS.
 *
 * OpenObjectStore OOS is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * OpenObjectStore OOS is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with OpenObjectStore OOS. If not, see <http://www.gnu.org/licenses/>.
 */

#include "database/sqlite/sqlite_result.hpp"
#include "database/row.hpp"

#include "tools/convert.hpp"

namespace oos {

namespace sqlite {

sqlite_result::sqlite_result()
  : pos_(-1)
{}

sqlite_result::~sqlite_result()
{
  while (!rows_.empty()) {
    row *r = rows_.back();
    delete r;
    rows_.pop_back();
  }
}

const char* sqlite_result::column(sqlite_result::size_type c) const
{
  return rows_.at(pos_)->at<std::string>(c).c_str();
}

bool sqlite_result::fetch()
{
  return ++pos_ < rows_.size();
}

sqlite_result::size_type sqlite_result::affected_rows() const
{
  return 0;
}

sqlite_result::size_type sqlite_result::result_rows() const
{
  return rows_.size();
}

sqlite_result::size_type sqlite_result::fields() const
{
  return 0;
}

void sqlite_result::push_back(row *r)
{
  rows_.push_back(r);
}

void sqlite_result::read(const char *id, char &x)
{
}

void sqlite_result::read(const char *id, short &x)
{
}

void sqlite_result::read(const char *id, int &x)
{
}

void sqlite_result::read(const char *, long &x)
{
  std::string val = rows_.at(pos_)->at<std::string>(result_index);
  convert(val, x);
  std::cout << "converted string [" << val << "] to long [" << x << "]\n";
//  x = rows_.at(pos_)->at<long>(result_index);
}

void sqlite_result::read(const char *id, unsigned char &x)
{
}

void sqlite_result::read(const char *id, unsigned short &x)
{
}

void sqlite_result::read(const char *id, unsigned int &x)
{
}

void sqlite_result::read(const char *id, unsigned long &x)
{
}

void sqlite_result::read(const char *id, bool &x)
{
}

void sqlite_result::read(const char *id, float &x)
{
}

void sqlite_result::read(const char *id, double &x)
{
}

void sqlite_result::read(const char *id, char *x, int s)
{
}

void sqlite_result::read(const char *id, varchar_base &x)
{
}

void sqlite_result::read(const char *id, std::string &x)
{
}

void sqlite_result::read(const char *id, object_base_ptr &x)
{
}

void sqlite_result::read(const char *id, object_container &x)
{
}

}

}
