#if defined( HAVE_CONFIG_H )
#include <config.hpp>
#endif

#include <iostream>
#include <array>

template <size_t N>
struct car : std::array<char, N>
{
  using array = std::array<char, N>;
  
  constexpr car() : array{} {}
  // constexpr car( char const ( &lit )[N + 1] ) : array{copyN( lit )} {}
  constexpr car( char const ( &lit )[N] ) : array{copyN( lit )} {}

private:
  // constexpr array copyN( char const ( &lit )[N + 1] )
  // {
  //   if( lit[N] ) throw( std::invalid_argument( "not zero terminated" ) );
  //   array a{};
  //   for( size_t i = 0; i < N; ++i ) a[i] = lit[i];
  //   return a;
  // }

  constexpr array copyN( char const ( &lit )[N] )
  {
    if( lit[N - 1] ) throw( std::invalid_argument( "not zero terminated" ) );
    array a{};
    for( size_t i = 0; i < N; ++i ) a[i] = lit[i];
    return a;
  }
};

// template <size_t N, size_t M>
// constexpr auto operator+( car<N> const &a, car<M> const &b )
// {
//   car<N + M> c;
//   for( size_t i = 0; i < N; ++i ) c[i] = a[i];
//   for( size_t i = 0; i < M; ++i ) c[i + N] = b[i];
//   return c;
// }

template <size_t N, size_t M>
constexpr auto operator+( car<N> const &a, car<M> const &b )
{
  car<N + M - 1> c;
  for( size_t i = 0; i < N - 1; ++i ) c[i] = a[i];
  for( size_t i = 0; i < M; ++i ) c[i + ( N - 1 )] = b[i];
  return c;
}

// Deduction of the +1 string literal length requires this deduction guide
// template <size_t N>
// car( char const ( & )[N] )->car<N - 1>;

constexpr int absX( int x ) { return x >= 0 ? x : -x; }
constexpr int powerX( int const &x )
{
  int y = 1;
  int z = absX( x );
  while( z >= 10 )
  {
    z /= 10;
    ++y;
  }
  return y;
}

template <int N>
constexpr auto to_car()
{
  car<powerX( N ) + 1> z;
  int j = absX(N);
  for( int i = 0; i < powerX( N ); ++i, j /= 10 )
  {
    z[powerX( N ) - i - 1] = (char)( '0' + ( j % 10 ) );
  }
  z[powerX( N )] = 0;

  if constexpr ( N < 0 )
    return car{"-"} + z;
  else
    return z;
}

constexpr auto frmtx_int()
{
  return car{u8"{:#0"} + to_car<sizeof( int ) * 2>() + car{u8"x}"};
}

// template<size_t N>
// struct olle
// {
//   char array[N];
// };

constexpr static car gccver = car{"G++ "} + to_car<__GNUC__>() + car{"."} + to_car<__GNUC_MINOR__>();

int main( int, char *[], char *[] )
{
  constexpr car a = u8"åäö";
  static_assert( sizeof( a ) == 7 );

  constexpr auto b = a + car{u8"car"};
  static_assert( sizeof( b ) == 10 );

  constexpr auto c = frmtx_int();
  static_assert( sizeof( c ) == 8 );

  constexpr auto d = car{u8"räksmörgås är gott att ta någon gång i bland"};
  static_assert( sizeof( d ) == 51 );

  constexpr auto e = to_car<-99>();
  static_assert( sizeof( e ) == 4 );

  std::cout << a.data() << " -> " << a.size() << ", " << a.max_size() << "\n";
  std::cout << b.data() << " -> " << b.size() << ", " << b.max_size() << "\n";
  std::cout << c.data() << " -> " << c.size() << ", " << c.max_size() << "\n";
  std::cout << d.data() << " -> " << d.size() << ", " << d.max_size() << "\n";
  std::cout << e.data() << " -> " << e.size() << ", " << e.max_size() << "\n";
  std::cout << gccver.data() << "\n";
}
