#if defined( HAVE_CONFIG_H )
#include <config.hpp>
#endif

#include <array>
#include <iostream>

namespace ct_zstr {

template<size_t N>
using zstr = std::array<char, N>;
  
namespace impl {

constexpr int absX( int x ) { return x >= 0 ? x : -x; }
constexpr int powerX( int x )
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

} // namespace impl

template <size_t N>
constexpr auto to_zstr( char const ( &litstr )[N] )
{
  if( litstr[N - 1] ) throw( std::invalid_argument( "not zero terminated" ) );
  std::array<char, N> arr_{};
  for( size_t i = 0; i < N; ++i )
    arr_[i] = litstr[i];

  return arr_;
}

template <int N>
constexpr auto int_zstr()
{
  std::array<char, impl::powerX( N ) + 1> z{};
  int j = impl::absX( N );
  for( int i = 0; i < impl::powerX( N ); ++i, j /= 10 )
  {
    z[static_cast<size_t>( ( impl::powerX( N ) - 1 ) - i )] = (char)( '0' + ( j % 10 ) );
  }
  z[impl::powerX( N )] = 0;

  if constexpr( N < 0 ) { return to_zstr( "-" ) + z; }
  else
    return z;
}

} // namespace ct_zstr

template <size_t N, size_t M>
constexpr auto operator+( std::array<char, N> const &a, std::array<char, M> const &b )
{
  std::array<char, N + M - 1> c{};
  for( size_t i = 0; i < N - 1; ++i )
    c[i] = a[i];
  for( size_t i = 0; i < M; ++i )
    c[i + ( N - 1 )] = b[i];
  return c;
}

template <size_t N, size_t M>
constexpr auto operator+( std::array<char, N> const &a, char const ( &b )[M] )
{
  std::array<char, N + M - 1> c{};
  for( size_t i = 0; i < N - 1; ++i )
    c[i] = a[i];
  for( size_t i = 0; i < M; ++i )
    c[i + ( N - 1 )] = b[i];
  return c;
}

constexpr auto frmtx_int()
{
  return ct_zstr::to_zstr( u8"{:#0" ) + ct_zstr::int_zstr<sizeof( int ) * 2>() + ct_zstr::to_zstr( u8"x}" );
}

constexpr static auto gccver = ct_zstr::to_zstr( "G++ " ) + ct_zstr::int_zstr<__GNUC__>() + ct_zstr::to_zstr( "." ) + ct_zstr::int_zstr<__GNUC_MINOR__>();

int main( int, char *[], char *[] )
{
  constexpr auto a = ct_zstr::to_zstr( u8"åäö" );
  static_assert( sizeof( a ) == 7 );

  constexpr auto b = a + ct_zstr::to_zstr( u8"car" );
  static_assert( sizeof( b ) == 10 );

  constexpr auto c = frmtx_int();
  static_assert( sizeof( c ) == 8 );

  constexpr auto d = ct_zstr::to_zstr( u8"räksmörgås är gott att ta någon gång i bland" );
  static_assert( sizeof( d ) == 51 );

  constexpr auto e = ct_zstr::int_zstr<-99>();
  static_assert( sizeof( e ) == 4 );

  std::cout << a.data() << " -> " << a.size() << ", " << a.max_size() << "\n";
  std::cout << b.data() << " -> " << b.size() << ", " << b.max_size() << "\n";
  std::cout << c.data() << " -> " << c.size() << ", " << c.max_size() << "\n";
  std::cout << d.data() << " -> " << d.size() << ", " << d.max_size() << "\n";
  std::cout << e.data() << " -> " << e.size() << ", " << e.max_size() << "\n";
  std::cout << gccver.data() << "\n";
}
