#include <common/Settings.hh>


unsigned int Settings::_depth; ///< depth buffer size
unsigned int Settings::_stencil; ///< stencil buffer size
unsigned int Settings::_antiAliasing; ///< anti aliasing level

// generic settings
bool Settings::_fullScreen; ///< notify if we're running in full screen
unsigned int Settings::_keyRepeatDelay; ///< required time to consider a "second pressure"


void Settings::initialize(unsigned int depth,
                          unsigned int stencil,
                          unsigned int antiAliasing)
{
  _depth = depth;
  _stencil = stencil;
  _antiAliasing= antiAliasing;
}
