/**
 * \file
 * \date November 2, 2019
 * \author Zermingore
 * \brief Debug class templates implementation
 */

#ifndef DEBUG_HXX_
# define DEBUG_HXX_

# include <debug/Debug.hh>



template<typename T, typename... Tail>
void constexpr Debug::logPrintf(const T head, const Tail... tail)
{
  logTime();
  bodylogprintf(head, tail...);

#   ifdef DEBUG
    printf(head, tail...);
#   endif
}



template<typename T>
constexpr void Debug::printLog(const T head)
{
  *_log << " " << head << COLOR_NORMAL;
}



template<typename T, typename... Tail>
void constexpr Debug::printf(const T head, const Tail... tail)
{
  std::cout << head << " ";
  if constexpr(sizeof...(Tail) > 0)
  {
    printf(tail...);
  }
  else
  {
    std::cout << COLOR_NORMAL << std::endl;
  }
}



template<typename T, typename... Tail>
void constexpr Debug::notice(const T head, const Tail... tail)
{
  logTime();
  *_log << COLOR_NOTICE;
  bodylogprintf(head, tail...);

#ifdef DEBUG
  std::cout << COLOR_NOTICE;
  printf(head, tail...);
#endif
}



template<typename T, typename... Tail>
void constexpr Debug::warning(const T head, const Tail... tail)
{
  logTime();
  *_log << COLOR_WARNING;
  bodylogprintf(head, tail...);

  std::cout << COLOR_WARNING;
  printf(head, tail...);
}



template<typename T, typename... Tail>
void constexpr Debug::error(const T head, const Tail... tail)
{
  logTime();
  *_log << COLOR_ERROR;
  bodylogprintf(head, tail...);

  std::cout << COLOR_ERROR;
  printf(head, tail...);
}



template<typename T, typename... Tail>
void constexpr Debug::bodylogprintf(const T head, const Tail... tail)
{
  printLog(head);

  if constexpr(sizeof...(Tail) > 0)
  {
    bodylogprintf(tail...);
  }
  else
  {
    *_log << std::endl;
  }
}

#endif // DEBUG_HXX_
