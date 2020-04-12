// auto-generated code, edit at your own risks
// generator: ./generate_enum_print.sh
// generated on: Sun Apr 12 19:51:46 CEST 2020


#include <string>
#include <common/enums/states.hh>

namespace debug {

std::string e_state_string(e_state entry);

std::string e_state_string(e_state entry)
{
  switch (entry)
  {
    case e_state::NONE:
      return "e_state::NONE (0)";
    case e_state::GLOBAL:
      return "e_state::GLOBAL (no explicit value)";
    case e_state::PLAYING:
      return "e_state::PLAYING (no explicit value)";
    case e_state::MAP_MENU:
      return "e_state::MAP_MENU (no explicit value)";
    case e_state::SELECTION_UNIT:
      return "e_state::SELECTION_UNIT (no explicit value)";
    case e_state::MOVING_UNIT:
      return "e_state::MOVING_UNIT (no explicit value)";
    case e_state::ACTION_MENU:
      return "e_state::ACTION_MENU (no explicit value)";
    case e_state::CREW_MANAGEMENT:
      return "e_state::CREW_MANAGEMENT (no explicit value)";
    case e_state::SELECTION_CREW:
      return "e_state::SELECTION_CREW (no explicit value)";
    case e_state::SELECT_TARGET:
      return "e_state::SELECT_TARGET (no explicit value)";
    case e_state::SELECT_DROP_ZONE:
      return "e_state::SELECT_DROP_ZONE (no explicit value)";
    default:
      return "entry not matched";
  }
}

} // namespace debug
