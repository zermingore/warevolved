#include <common/Settings.hh>

Settings::Settings()
{
}

Settings::Settings(unsigned int depth,
				   unsigned int stencil,
				   unsigned int antialiasing)
{
  _depth = depth;
  _stencil = stencil;
  _antialiasing = antialiasing;
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

unsigned int Settings::getAntialiasing()
{
  return _antialiasing;
}

bool Settings::getFullscreen()
{
  return _fullscreen;
}


void Settings::setDepth(unsigned int depth)
{
  _depth = depth;
}

void Settings::setStencil(unsigned int stencil)
{
  _stencil = stencil;
}

void Settings::setAntialiasing(unsigned int antialiasing)
{
  _antialiasing = antialiasing;
}

/// generic settings
void Settings::setFullscreen(bool fullscreen)
{
  _fullscreen = fullscreen;
}
