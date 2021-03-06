//
// Created by sascha on 3/4/16.
//
#include "sql/basic_dialect.hpp"
#include "sql/basic_dialect_compiler.hpp"
#include "sql/basic_dialect_linker.hpp"
#include "sql/sql.hpp"

namespace oos {

namespace detail {

build_info::build_info(const sql &s, basic_dialect *d)
  : dialect(d)
{
  tokens_.assign(s.token_list_.begin(),s.token_list_.end());
  current = tokens_.begin();
}

}

basic_dialect::basic_dialect(detail::basic_dialect_compiler *compiler, detail::basic_dialect_linker *linker)
  : compiler_(compiler)
  , linker_(linker)
{
  compiler_->dialect(this);
  linker_->dialect(this);
}

basic_dialect::~basic_dialect()
{
  delete compiler_;
  delete linker_;
}

std::string basic_dialect::direct(const sql &s)
{
  return build(s, DIRECT);
}

std::string basic_dialect::prepare(const sql &s)
{
  return build(s, PREPARED);
}

std::string basic_dialect::build(const sql &s, t_compile_type compile_type)
{
  compile_type_ = compile_type;

  push(s);
  compile();
  link();
  std::string result(top().result);
  pop();
  return result;
}

void basic_dialect::compile()
{
  compiler_->compile(*this);
}

void basic_dialect::link()
{
  linker_->link();
}

bool basic_dialect::is_preparing() const
{
  return compile_type_ == PREPARED;
}

void basic_dialect::replace_token(detail::token::t_token tkn, const std::string &value)
{
  tokens[tkn] = value;
}

void basic_dialect::append_to_result(const std::string &part)
{
  top().result += part;
}

void basic_dialect::push(const sql &s)
{
  build_info_stack_.push(detail::build_info(s, this));
}

void basic_dialect::pop()
{
  build_info_stack_.pop();
}

detail::build_info &basic_dialect::top()
{
  return build_info_stack_.top();
}

size_t basic_dialect::inc_bind_count()
{
  return ++bind_count_;
}

size_t basic_dialect::inc_bind_count(size_t val)
{
  bind_count_ += val;
  return bind_count_;
}

size_t basic_dialect::dec_bind_count()
{
  return --bind_count_;
}

size_t basic_dialect::inc_column_count()
{
  return ++column_count_;
}

size_t basic_dialect::dec_column_count()
{
  return --column_count_;
}

size_t basic_dialect::bind_count() const
{
  return bind_count_;
}

size_t basic_dialect::column_count() const
{
  return column_count_;
}

std::string basic_dialect::token_at(detail::token::t_token tok) const
{
  return tokens.at(tok);
}

basic_dialect::t_compile_type basic_dialect::compile_type() const
{
  return compile_type_;
}

}