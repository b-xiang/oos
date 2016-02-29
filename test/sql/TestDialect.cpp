//
// Created by sascha on 2/26/16.
//

#include "TestDialect.hpp"

#include "sql/token.hpp"
#include "sql/types.hpp"

#include <algorithm>

using namespace oos;

const char* TestDialect::type_string(data_type_t type) const
{
  switch(type) {
    case type_char:
      return "INTEGER";
    case type_short:
      return "INTEGER";
    case type_int:
      return "INTEGER";
    case type_long:
      return "INTEGER";
    case type_unsigned_char:
      return "INTEGER";
    case type_unsigned_short:
      return "INTEGER";
    case type_unsigned_int:
      return "INTEGER";
    case type_unsigned_long:
      return "INTEGER";
    case type_bool:
      return "INTEGER";
    case type_float:
      return "DOUBLE";
    case type_double:
      return "DOUBLE";
    case type_char_pointer:
      return "VARCHAR";
    case type_varchar:
      return "VARCHAR";
    case type_text:
      return "TEXT";
    case type_date:
      return "REAL";
    case type_time:
      return "TEXT";
    default:
    {
      std::stringstream msg;
      msg << "test dialect: unknown data type [" << type << "]";
      throw std::logic_error(msg.str());
      //throw std::logic_error("mysql sql: unknown type");
    }
  }
}

std::string TestDialect::compile(oos::detail::limit &limit)
{
  return "";
}

std::string TestDialect::compile(oos::detail::remove &remove1)
{
  return "";
}

std::string TestDialect::compile(oos::detail::basic_value &value)
{
  return "";
}

std::string TestDialect::compile(oos::detail::insert &insert)
{
  return "";
}

std::string TestDialect::compile(oos::detail::group_by &by)
{
  return "";
}

std::string TestDialect::compile(oos::detail::desc &desc)
{
  return "";
}

std::string TestDialect::compile(oos::detail::asc &asc)
{
  return "";
}

std::string TestDialect::compile(oos::detail::order_by &by)
{
  return "";
}

std::string TestDialect::compile(oos::detail::basic_condition &token)
{
  return "";
}

std::string TestDialect::compile(oos::detail::where &where)
{
  return "";
}

std::string TestDialect::compile(oos::detail::from &from)
{
  return "";
}

std::string TestDialect::compile(oos::detail::varchar_column &column)
{
  std::stringstream str;
  str << column.name << " " << type_string(column.type) << "(" << column.size << ")";
  return str.str();
}

std::string TestDialect::compile(oos::detail::identifier_column &column)
{
  return column.name + " " + type_string(column.type) + " NOT NULL PRIMARY KEY";
}

std::string TestDialect::compile(oos::detail::column &column)
{
  return column.name;
}

std::string TestDialect::compile(oos::detail::typed_column &column)
{
  return column.name + " " + type_string(column.type);
}

std::string TestDialect::compile(oos::detail::columns &columns)
{
  std::string result("(");

  if (columns.columns_.size() > 1) {
    std::for_each(columns.columns_.begin(), columns.columns_.end() - 1, [&](const std::shared_ptr<detail::column> &col)
    {
      result += col->compile(*this, detail::token::DIRECT);
      result += ", ";
    });
  }
  if (!columns.columns_.empty()) {
    result += columns.columns_.back()->compile(*this, detail::token::DIRECT);
  }
  result += ") ";
  return result;
}

std::string TestDialect::compile(oos::detail::set &set)
{
  return "";
}

std::string TestDialect::compile(oos::detail::update &update)
{
  return "";
}

std::string TestDialect::compile(oos::detail::distinct &distinct)
{
  return "";
}

std::string TestDialect::compile(oos::detail::select &select1)
{
  return token(select1.type) + " ";
}

std::string TestDialect::compile(oos::detail::drop &drop)
{
  return token(drop.type) + " " + drop.table + " ";
}

std::string TestDialect::compile(oos::detail::create &create)
{
  return token(create.type) + " " + create.table + " ";
}
