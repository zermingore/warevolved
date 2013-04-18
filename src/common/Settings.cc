#include <common/Settings.hh>

Settings::Settings()
{
}

Settings::Settings(unsigned int depth,
				   unsigned int stencil,
				   unsigned int antiAliasing)
{
  _depth = depth;
  _stencil = stencil;
  _antiAliasing = antiAliasing;
}

Settings::~Settings()
{
}


unsigned int Settings::getDepth()
{
  return _depth;
}

unsigned int Settings::getStencil()
{
  return _stencil;
}

unsigned int Settings::getAntiAliasing()
{
  return _antiAliasing;
}

bool Settings::getFullScreen()
{
  return _fullScreen;
}


void Settings::setDepth(unsigned int depth)
{
  _depth = depth;
}

void Settings::setStencil(unsigned int stencil)
{
  _stencil = stencil;
}

void Settings::setAntiAliasing(unsigned int antiAliasing)
{
  _antiAliasing = antiAliasing;
}

/// generic settings
void Settings::setFullScreen(bool fullScreen)
{
  _fullScreen = fullScreen;
}
