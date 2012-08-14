#include "json/json_string.hpp"

#include <cctype>

namespace oos {

json_string::json_string()
  : json_type("json_string")
{}

json_string::json_string(const std::string &val)
  : json_type("json_string")
  , value_(val)
{}

json_string::json_string(const char *val)
  : json_type("json_string")
  , value_(val)
{}

json_string::json_string(const json_string &x)
  : json_type("json_string")
  , value_(x.value_)
{}

json_string::json_string(const json_value &x)
  : json_type("json_string")
{
  const json_string *s = x.value_type<json_string>();
  if (s) {
    value_ = s->value();
  } else {
    throw std::logic_error("json_value isn't of type json_string");
  }
}

json_string& json_string::operator=(const json_string &x)
{
  value_ = x.value_;
  return *this;
}

json_string& json_string::operator=(const json_value &x)
{
  const json_string *s = x.value_type<json_string>();
  if (s) {
    value_ = s->value();
  } else {
    throw std::logic_error("json_value isn't of type json_string");
  }
  return *this;
}

json_string& json_string::operator=(const std::string &x)
{
  value_ = x;
  return *this;
}

json_string::~json_string()
{}

bool json_string::operator<(const json_string &x) const
{
  return value_ < x.value_;
}

bool json_string::parse(std::istream &in)
{
  // skip white
  in >> std::ws;
  
  // parse string
  char c = in.get();
  if (in.good() && c != '"') {
    // invalid key
    in.putback(' ');
    in.putback(c);
    return false;
  }

  value_.clear();
  // read until next '"' or eof of stream

  while (in && in.good()) {
    c = in.get();
    if (!in.good()) {
      continue;
    }

    if (c == '"') {
      // read closing double quote
      break;
    } else {
      value_.push_back(c);
    }
  }
  return true;
}

void json_string::print(std::ostream &out) const
{
  out << "\"" << value_ << "\"";
}

std::string json_string::value() const
{
  return value_;
}

void json_string::value(const std::string &val)
{
  value_ = val;
}

void json_string::push_back(char c)
{
  value_.push_back(c);
}

}
