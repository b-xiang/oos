#ifndef QUERY_HPP
#define QUERY_HPP

#include "database/sql.hpp"

#include <memory>
#include <sstream>

namespace oos {

class result;
class session;
class statement;
class database;
class object;
class prototype_node;
class condition;
class object_atomizable;

class query
{
private:
  enum state_t {
    QUERY_BEGIN,
    QUERY_CREATE,
    QUERY_DROP,
    QUERY_OBJECT_SELECT,
    QUERY_OBJECT_INSERT,
    QUERY_OBJECT_UPDATE,
    QUERY_SELECT,
    QUERY_INSERT,
    QUERY_UPDATE,
    QUERY_DELETE,
    QUERY_COLUMN,
    QUERY_SET,
    QUERY_FROM,
    QUERY_WHERE,
    QUERY_COND_WHERE,
    QUERY_AND,
    QUERY_OR,
    QUERY_ORDERBY,
    QUERY_GROUPBY,
    QUERY_EXECUTED,
    QUERY_PREPARED,
    QUERY_BOUND
  };

public:
  query(session &s);
  query(database &s);
  ~query();

  query& create(const prototype_node &node);
  query& create(const std::string &name, object_atomizable *o);
  query& drop(const prototype_node &node);
  query& drop(const std::string &name);
  query& select(const prototype_node &node);
  query& insert(object *o);
  query& insert(object_atomizable *o, const std::string &type);
  query& update(object *o);
  query& update(const std::string &name, object_atomizable *o);
  query& remove(const prototype_node &node);
  query& where(const std::string &clause);
  query& where(const condition &c);
  query& and_(const condition &c);
  query& or_(const condition &c);
  query& order_by(const std::string &by);
  query& limit(int l);
  query& group_by(const std::string &field);

  query& select();
  query& select(object_atomizable *o);
  query& column(const std::string &name, sql::data_type_t type);
  query& from(const std::string &table);

  query& update(const std::string &table);
  template < class T >
  query& set(const std::string &name, sql::data_type_t type, const T &val)
  {
    throw_invalid(QUERY_SET, state);

    if (state == QUERY_SET) {
      sql_.append(", ");
    }

    sql_.append(name + "=");
    std::stringstream valstr;
    valstr << val;
    sql_.append(name.c_str(), type, valstr.str());

    state = QUERY_SET;

    return *this;
  }

  result* execute();
  statement* prepare();

  query& reset();
  
private:
  void throw_invalid(state_t next, state_t current) const;

private:
  sql sql_;
  state_t state;
  database &db_;
  std::unique_ptr<statement> stmt;
};

}

#endif /* QUERY_HPP */
