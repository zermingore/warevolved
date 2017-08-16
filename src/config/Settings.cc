#include <config/Settings.hh>


// static fields definitions
unsigned int Settings::_depth;
unsigned int Settings::_stencil;
unsigned int Settings::_antiAliasing;
bool Settings::_fullScreen;
size_t Settings::_keyRepeatDelay;


void Settings::initialize(const unsigned int depth,
                          const unsigned int stencil,
                          const unsigned int antiAliasing)
{
  _depth = depth;
  _stencil = stencil;
  _antiAliasing = antiAliasing;
}
