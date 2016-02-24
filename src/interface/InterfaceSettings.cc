#include <interface/InterfaceSettings.hh>

namespace interface {

InterfaceSettings::InterfaceSettings(Color player_color)
  : _cursorColor(player_color)
  , _unitsColor(player_color)
{
}


} // namespace interface