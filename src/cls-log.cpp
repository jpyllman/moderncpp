#if defined( HAVE_CONFIG_H )
#include <config.hpp>
#endif

#include "cls-log.hpp"

#include <iostream>
#include <locale>

namespace cls { namespace log {

basic::basic()
{
  std::clog << "basic::basic()                           { c='" << c << "', o='"
            << o << "' }[" << this << "]\n";
}

basic::basic( char z )
{
  iset( z );
  std::clog << "basic::basic( char )                     { c='" << c << "', o='"
            << o << "' }[" << this << "]\n";
}

basic::~basic()
{
  std::clog << "basic::~basic()                          { c='" << c << "', o='"
            << o << "' }[" << this << "]\n";
}

basic::basic( basic const &z )
{
  iset( std::toupper( z.c, std::locale() ) );
  std::clog << "basic::basic( basic const & )            { c='" << c << "', o='"
            << o << "' }[" << this << "][" << &z << "]\n";
}

basic &basic::operator=( basic const &z )
{
  iset( std::toupper( z.c, std::locale() ) );
  std::clog << "basic& basic::operator=( basic const & ) { c='" << c << "', o='"
            << o << "' }[" << this << "][" << &z << "]\n";

  return *this;
}

basic::basic( basic &&z )
{
  iset( std::toupper( z.c, std::locale() ) );
  z.iset( '-' );
  std::clog << "basic::basic( basic && )                 { c='" << c << "', o='"
            << o << "' }[" << this << "][" << &z << "]\n";
}

basic &basic::operator=( basic &&z )
{
  iset( std::toupper( z.c, std::locale() ) );
  z.iset( '_' );
  std::clog << "basic& basic::operator=( basic && )      { c='" << c << "', o='"
            << o << "' }[" << this << "][" << &z << "]\n";

  return *this;
}

}} // namespace cls::log
