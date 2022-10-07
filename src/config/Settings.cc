/**
 * \file
 * \date Auguts 10, 2020
 * \author Zermingore
 * \brief Settings static class definition
 */

#include <sstream>

#include <config/Settings.hh>

#include <debug/Debug.hh>



void Settings::setFullScreen(bool fullScreen)
{
  _fullScreen = fullScreen;
  if (fullScreen)
  {
    setGraphics(24, 8, 4);
  }
  else
  {
    setGraphics(0, 0, 0); // vanilla (debug) mode
  }
}


std::string Settings::versionString()
{
  auto version { Settings::version() };

  std::stringstream sstr;
  sstr << *(version.begin());
  for (auto it = version.begin() + 1; it != version.end(); ++it)
  {
    sstr << '.' << *it;
  }

  return sstr.str();
}
