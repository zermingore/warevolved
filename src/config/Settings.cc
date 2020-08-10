/**
 * \file
 * \date Auguts 10, 2020
 * \author Zermingore
 * \brief Settings static class definition
 */

#include <sstream>

#include <config/Settings.hh>

#include <debug/Debug.hh>


unsigned int Settings::_depth;
unsigned int Settings::_stencil;
unsigned int Settings::_antiAliasing;

bool Settings::_fullScreen;

const std::vector<std::size_t> Settings::_version = {0, 1, 0};



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
