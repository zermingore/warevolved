#include <common/Settings.hh>


// static fields definitions
unsigned int Settings::_depth;
unsigned int Settings::_stencil;
unsigned int Settings::_antiAliasing;
bool Settings::_fullScreen;
unsigned int Settings::_keyRepeatDelay;


void Settings::initialize(unsigned int depth,
                          unsigned int stencil,
                          unsigned int antiAliasing)
{
  _depth = depth;
  _stencil = stencil;
  _antiAliasing= antiAliasing;
}
