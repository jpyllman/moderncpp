#if defined( HAVE_CONFIG_H )
#include <config.hpp>
#endif

#include "cls-log.hpp"

#include <utility>

cls::log::basic factory_z()
{
  cls::log::basic z( 'z' );
  return z;
}

int main( int, char *[], char *[] )
{
  cls::log::basic a{};
  cls::log::basic b{'b'};
  cls::log::basic const c{'c'};
  cls::log::basic d{b};
  cls::log::basic const e{b};
  cls::log::basic f{cls::log::basic( 'f' )};
  cls::log::basic g{std::move( b )};
  cls::log::basic h{std::move( c )};
  cls::log::basic i{'i'};
  cls::log::basic j{'j'};
  i = j;
  cls::log::basic k{factory_z()};
  cls::log::basic l{'l'};
  cls::log::basic m{'m'};
  m = std::move( l );
}
