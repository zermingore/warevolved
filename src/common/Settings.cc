#include <common/Settings.hh>


Settings::Settings(unsigned int depth,
                   unsigned int stencil,
                   unsigned int antiAliasing) :
  _depth (depth),
  _stencil (stencil),
  _antiAliasing (antiAliasing),
  _fullScreen (false),
  _keyRepeatDelay(0)
{
}
