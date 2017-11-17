#if defined( HAVE_CONFIG_H )
#include <config.hpp>
#endif

#include "cls-log.hpp"

#include <algorithm>

int main( int, char *[], char *[] )
{
  cls::log::basic x;
  auto y = x;
  auto z = std::move( x );

  y = z;
}
