/**
 * \brief Debug class implementation
 */

# ifdef __unix__
#   include <sys/prctl.h>
# endif

#include <debug/Debug.hh>

// Debug::_log definition
std::unique_ptr<std::ofstream> Debug::_log{
  std::make_unique<std::ofstream> (LOG_FILENAME, std::ios_base::out)};



void Debug::bodylogprintf()
{
  *_log << std::endl;
  std::cout << std::endl;
}



void Debug::printf()
{
  std::cout << COLOR_NORMAL << std::endl;
}



void Debug::logTime()
{
  const auto now{std::time(nullptr)};
  const auto full_date{*std::localtime(&now)};
  *_log << std::put_time(&full_date, "%F @ %T") << '\t';
}



void Debug::setThisThreadName(const std::string& name)
{
# ifdef __unix__
  prctl(PR_SET_NAME, name.c_str(), 0, 0, 0);
# endif
}
