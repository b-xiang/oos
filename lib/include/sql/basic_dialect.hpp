//
// Created by sascha on 2/25/16.
//

#ifndef OOS_BASIC_DIALECT_HPP
#define OOS_BASIC_DIALECT_HPP

#include "sql/types.hpp"

#include <unordered_map>
#include <string>

namespace oos {

namespace detail {

struct select;
struct insert;
struct update;
struct remove;
struct columns;
struct column;
struct typed_column;
struct identifier_column;
struct varchar_column;
struct basic_condition;
struct basic_value;
struct distinct;
struct set;
struct asc;
struct desc;
struct from;
struct where;
struct create;
struct drop;
struct limit;
struct order_by;
struct group_by;
}

class basic_dialect
{
public:
  enum t_token
  {
    CREATE_TABLE = 0,
    DROP,
    DELETE,
    INSERT,
    VALUES,
    VALUE,
    UPDATE,
    SELECT,
    COLUMNS,
    COLUMN,
    FROM,
    WHERE,
    AND,
    OR,
    ORDER_BY,
    GROUP_BY,
    ASC,
    DESC,
    LIMIT,
    OFFSET,
    DISTINCT,
    CLAUSE,
    SET,
    NOT_NULL,
    PRIMARY_KEY
  };

public:
  virtual ~basic_dialect() {}

  std::string token(t_token tok) const { return tokens.at(tok); }

  virtual const char* type_string(data_type_t type) const = 0;

  virtual std::string compile(oos::detail::create &) = 0;
  virtual std::string compile(oos::detail::drop &) = 0;
  virtual std::string compile(oos::detail::select &) = 0;
  virtual std::string compile(oos::detail::distinct &) = 0;
  virtual std::string compile(oos::detail::update &) = 0;
  virtual std::string compile(oos::detail::set &) = 0;
  virtual std::string compile(oos::detail::columns &) = 0;
  virtual std::string compile(oos::detail::column &) = 0;
  virtual std::string compile(oos::detail::typed_column &) = 0;
  virtual std::string compile(oos::detail::identifier_column &) = 0;
  virtual std::string compile(oos::detail::varchar_column &) = 0;
  virtual std::string compile(oos::detail::from &) = 0;
  virtual std::string compile(oos::detail::where &) = 0;
  virtual std::string compile(oos::detail::basic_condition &) = 0;
  virtual std::string compile(oos::detail::order_by &) = 0;
  virtual std::string compile(oos::detail::asc &) = 0;
  virtual std::string compile(oos::detail::desc &) = 0;
  virtual std::string compile(oos::detail::group_by &) = 0;
  virtual std::string compile(oos::detail::insert &) = 0;
  virtual std::string compile(oos::detail::basic_value &) = 0;
  virtual std::string compile(oos::detail::remove &) = 0;
  virtual std::string compile(oos::detail::limit &) = 0;

private:
  typedef std::unordered_map<t_token, std::string, std::hash<int>> t_token_map;
  const t_token_map tokens {
    {basic_dialect::CREATE_TABLE, "CREATE TABLE"},
    {basic_dialect::DROP, "DROP TABLE"},
    {basic_dialect::DELETE, "DELETE FROM"},
    {basic_dialect::INSERT, "INSERT INTO"},
    {basic_dialect::VALUES, "VALUES"},
    {basic_dialect::UPDATE, "UPDATE"},
    {basic_dialect::SELECT, "SELECT"},
    {basic_dialect::COLUMNS, "COLUMNS"},
    {basic_dialect::COLUMN, "COLUMN"},
    {basic_dialect::FROM, "FROM"},
    {basic_dialect::WHERE, "WHERE"},
    {basic_dialect::AND, "AND"},
    {basic_dialect::OR, "OR"},
    {basic_dialect::ORDER_BY, "ORDER BY"},
    {basic_dialect::GROUP_BY, "GROUP BY"},
    {basic_dialect::ASC, "ASC"},
    {basic_dialect::DESC, "DESC"},
    {basic_dialect::LIMIT, "LIMIT"},
    {basic_dialect::OFFSET, "OFFSET"},
    {basic_dialect::DISTINCT, "DISTINCT"},
    {basic_dialect::SET, "SET"},
    {basic_dialect::NOT_NULL, "NOT NULL"},
    {basic_dialect::PRIMARY_KEY, "PRIMARY KEY"}
  };
};

}
#endif //OOS_BASIC_DIALECT_HPP
