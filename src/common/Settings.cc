#include <common/Settings.hh>
#include <common/constants.hh>


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
