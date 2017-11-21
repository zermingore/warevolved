/**
 * \file
 * \date April 15, 2013
 * \author Zermingore
 * \brief Global settings class definition.
 */

#include <config/Settings.hh>



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



void Settings::setGraphics(unsigned int depth,
                           unsigned int stencil,
                           unsigned int antiAliasing)
{
  _depth = depth;
  _stencil = stencil;
  _antiAliasing = antiAliasing;
}
