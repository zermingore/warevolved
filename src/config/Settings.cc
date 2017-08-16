#include <config/Settings.hh>




void Settings::setFullScreen(const bool fullScreen)
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


void Settings::setGraphics(const unsigned int depth,
                           const unsigned int stencil,
                           const unsigned int antiAliasing)
{
  _depth = depth;
  _stencil = stencil;
  _antiAliasing = antiAliasing;
}
