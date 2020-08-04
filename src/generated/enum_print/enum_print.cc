// auto-generated code, edit at your own risks
// generator: generate_enum_print.sh
// generated on: Tue 04 Aug 2020 10:56:43 AM CEST



#include <string>

#include <generated/enum_print/enum_print.hh>


namespace debug {



std::string e_input_string(e_input entry)
{
  switch (entry)
  {
    case e_input::MOVE_UP:
      return "e_input::MOVE_UP (0)";
    case e_input::MOVE_DOWN:
      return "e_input::MOVE_DOWN (no explicit value)";
    case e_input::MOVE_LEFT:
      return "e_input::MOVE_LEFT (no explicit value)";
    case e_input::MOVE_RIGHT:
      return "e_input::MOVE_RIGHT (no explicit value)";
    case e_input::SELECTION:
      return "e_input::SELECTION (no explicit value)";
    case e_input::TOGGLE_PANEL:
      return "e_input::TOGGLE_PANEL (no explicit value)";
    case e_input::SCREENSHOT:
      return "e_input::SCREENSHOT (no explicit value)";
    case e_input::DUMP_MAP:
      return "e_input::DUMP_MAP (no explicit value)";
    case e_input::QUICK_SAVE:
      return "e_input::QUICK_SAVE (no explicit value)";
    case e_input::QUICK_LOAD:
      return "e_input::QUICK_LOAD (no explicit value)";
    case e_input::EXIT:
      return "e_input::EXIT (no explicit value)";
    case e_input::NB_KEYS:
      return "e_input::NB_KEYS (no explicit value)";
    default:
      return "entry not matched";
  }
}


std::string e_terrain_string(e_terrain entry)
{
  switch (entry)
  {
    case e_terrain::NONE:
      return "e_terrain::NONE (0)";
    case e_terrain::PLAIN:
      return "e_terrain::PLAIN (no explicit value)";
    case e_terrain::FOREST:
      return "e_terrain::FOREST (no explicit value)";
    case e_terrain::NB_TERRAIN:
      return "e_terrain::NB_TERRAIN (no explicit value)";
    default:
      return "entry not matched";
  }
}


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
    case e_state::EDIT_MAP:
      return "e_state::EDIT_MAP (no explicit value)";
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


std::string e_attack_result_string(e_attack_result entry)
{
  switch (entry)
  {
    case e_attack_result::INVALID:
      return "e_attack_result::INVALID (0)";
    case e_attack_result::NONE_DIED:
      return "e_attack_result::NONE_DIED (no explicit value)";
    case e_attack_result::ATTACKER_DIED:
      return "e_attack_result::ATTACKER_DIED (no explicit value)";
    case e_attack_result::DEFENDER_DIED:
      return "e_attack_result::DEFENDER_DIED (no explicit value)";
    case e_attack_result::BOTH_DIED:
      return "e_attack_result::BOTH_DIED (no explicit value)";
    default:
      return "entry not matched";
  }
}


std::string e_unit_string(e_unit entry)
{
  switch (entry)
  {
    case e_unit::SOLDIER:
      return "e_unit::SOLDIER (0)";
    case e_unit::CAR:
      return "e_unit::CAR (no explicit value)";
    case e_unit::MOTORCYCLE:
      return "e_unit::MOTORCYCLE (no explicit value)";
    case e_unit::NB_UNITS:
      return "e_unit::NB_UNITS (no explicit value)";
    case e_unit::NONE:
      return "e_unit::NONE (no explicit value)";
    default:
      return "entry not matched";
  }
}

} // namespace debug
