/**
 * \file
 * \date Jul 23, 2013
 * \author Zermingore
 * \brief Debug macros definition
 */

# ifdef __unix__
#   include <sys/prctl.h>
# endif

#include <filesystem>

#include <debug/Debug.hh>



void Debug::init()
{
  try
  {
    if (std::filesystem::exists(LOG_FILENAME))
    {
      std::filesystem::rename(LOG_FILENAME, LOG_FILENAME_OLD);
    }
  }
  catch (std::filesystem::filesystem_error& e)
  {
    std::cout << "Error moving the old log: " << e.what() << "... ignoring\n";
  }

  _log = std::make_unique<std::ofstream> (LOG_FILENAME, std::ios_base::out);
  NOTICE("Logging into:", LOG_FILENAME); // Using the log, checking if it works
}



void Debug::logTime()
{
  const auto now{std::time(nullptr)};
  const auto full_date{*std::localtime(&now)};
  *_log << std::put_time(&full_date, "%F @ %T") << '\t';
}



void Debug::printOnce(const std::string& str)
{
  try
  {
    if (_printedOnce.at(str)) // avoid ignoring return value
      return;
  }
  catch ([[maybe_unused]] const std::out_of_range& e)
  {
    PRINTF(str);
    _printedOnce[str] = true;
  }
}



void Debug::setThisThreadName(const std::string& name)
{
# ifdef __unix__
  prctl(PR_SET_NAME, name.c_str(), 0, 0, 0);
# endif
}
