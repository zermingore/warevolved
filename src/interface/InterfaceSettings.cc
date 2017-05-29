#include <interface/InterfaceSettings.hh>

namespace interface {

InterfaceSettings::InterfaceSettings(const graphics::Color player_color)
  : _cursorColor(player_color)
  , _unitsColor(player_color)
{
}


} // namespace interface
