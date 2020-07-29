/**
 * \file
 * \brief Debug class templates implementation
 * \author Zermingore
 * \date November 2, 2019
 */

#include <debug/Debug.hh>


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
