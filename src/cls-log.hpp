#if !defined( CLS_LOG_HPP )
#define CLS_LOG_HPP

namespace cls { namespace log {

class basic
{
public:
  basic();
  ~basic();

  basic( basic const & );
  basic &operator=( basic const & );

  basic( basic && );
  basic &operator=( basic && );
};

}} // namespace cls::log

#endif // !defined( CLS_LOG_HPP )
