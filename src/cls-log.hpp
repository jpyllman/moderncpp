#if !defined( CLS_LOG_HPP )
#define CLS_LOG_HPP

namespace cls { namespace log {

class basic final
{
  char c = ' ';
  char o = '|';

public:
  // constructors
  basic();
  explicit basic( char );

  // destructor
  ~basic();

  // copy constructor/assignment
  basic( basic const & );
  basic &operator=( basic const & );

  // move constructor/assignment
  basic( basic && );
  basic &operator=( basic && );

private:
  void iset( char const z ) { o = c; c = z; }
};

}} // namespace cls::log

#endif // !defined( CLS_LOG_HPP )
