#include <common/debug/Debug.hh>

// Debug::_log definition
// not using auto to help g++
std::unique_ptr<std::ofstream> Debug::_log(std::make_unique<std::ofstream>
                                           (LOG_FILENAME, std::ios_base::out));


void Debug::bodylogprintf()
{
  *_log << std::endl;
  std::cout << std::endl;
}


void Debug::printf()
{
  std::cout << COLOR_NORMAL << std::endl;
}
