#if defined( HAVE_CONFIG_H )
#include <config.hpp>
#endif

#include "cls-log.hpp"

#include <iostream>

namespace cls { namespace log {

basic::basic() { std::clog << "basic::basic() [" << this << "]\n"; }

basic::~basic() { std::clog << "basic::~basic() [" << this << "]\n"; }

basic::basic( basic const &a )
{
  std::clog << "basic::basic( basic const & ) [" << this << "][" << &a << "]\n";
}

basic &basic::operator=( basic const &a )
{
  std::clog << "basic& basic::operator=( basic const & ) [" << this << "]["
            << &a << "]\n";
  return *this;
}

basic::basic( basic &&a )
{
  std::clog << "basic::basic( basic && ) [" << this << "][" << &a << "]\n";
}

basic &basic::operator=( basic &&a )
{
  std::clog << "basic& basic::operator=( basic && ) [" << this << "][" << &a
            << "]\n";
  return *this;
}

}} // namespace cls::log
