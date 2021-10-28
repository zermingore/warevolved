/**
 * \file
 * \author generate_enum_print.sh
 * \brief Wrapper enum <=> string
 * \warning auto-generated code, edit at your own risks
 */


#include <string>

#include <generated/enum_print/enum_print.hh>
#include <game/ItemsContainer.hh>
#include <game/Terrain.hh>
#include <game/Map.hh>
#include <game/Item.hh>
#include <game/PathFinding.hh>
#include <game/units/Unit.hh>
#include <input/ReplayManager.hh>
#include <input/EventManager.hh>
#include <input/KeyManager.hh>
#include <tools/options/Option.hh>
#include <resources/ResourcesManager.hh>
#include <interface/menus/MenuEntry.hh>
#include <interface/Panel.hh>
#include <context/State.hh>


namespace debug {



std::string e_container_type_string(e_container_type entry)
{
  switch (entry)
  {
    case e_container_type::EQUIPPED:
      return "e_container_type::EQUIPPED (no explicit value)";
    case e_container_type::BACKPACK:
      return "e_container_type::BACKPACK (no explicit value)";
    case e_container_type::POCKET:
      return "e_container_type::POCKET (no explicit value)";
    case e_container_type::TRUNK:
      return "e_container_type::TRUNK (no explicit value)";
    case e_container_type::CELL:
      return "e_container_type::CELL (no explicit value)";
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
    case e_terrain::BUILDING_DOOR:
      return "e_terrain::BUILDING_DOOR (no explicit value)";
    case e_terrain::BUILDING_WINDOW:
      return "e_terrain::BUILDING_WINDOW (no explicit value)";
    case e_terrain::BUILDING_WINDOW_FIRST:
      return "e_terrain::BUILDING_WINDOW_FIRST (no explicit value)";
    case e_terrain::BUILDING_LAST_STAGE:
      return "e_terrain::BUILDING_LAST_STAGE (no explicit value)";
    case e_terrain::BUILDING_ROOF:
      return "e_terrain::BUILDING_ROOF (no explicit value)";
    case e_terrain::NB_TERRAIN:
      return "e_terrain::NB_TERRAIN (no explicit value)";
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


std::string e_rotation_string(e_rotation entry)
{
  switch (entry)
  {
    case e_rotation::ROT_0:
      return "e_rotation::ROT_0 (0)";
    case e_rotation::ROT_90:
      return "e_rotation::ROT_90 (90)";
    case e_rotation::ROT_180:
      return "e_rotation::ROT_180 (180)";
    case e_rotation::ROT_270:
      return "e_rotation::ROT_270 (270)";
    default:
      return "entry not matched";
  }
}


std::string e_item_slot_string(e_item_slot entry)
{
  switch (entry)
  {
    case e_item_slot::NONE:
      return "e_item_slot::NONE (no explicit value)";
    case e_item_slot::MAIN_WEAPON:
      return "e_item_slot::MAIN_WEAPON (no explicit value)";
    case e_item_slot::SECONDARY_WEAPON:
      return "e_item_slot::SECONDARY_WEAPON (no explicit value)";
    case e_item_slot::HEAD:
      return "e_item_slot::HEAD (no explicit value)";
    case e_item_slot::TORSO:
      return "e_item_slot::TORSO (no explicit value)";
    case e_item_slot::LEGS:
      return "e_item_slot::LEGS (no explicit value)";
    default:
      return "entry not matched";
  }
}


std::string e_path_shape_string(e_path_shape entry)
{
  switch (entry)
  {
    case e_path_shape::LAST_UP:
      return "e_path_shape::LAST_UP (0)";
    case e_path_shape::LAST_DOWN:
      return "e_path_shape::LAST_DOWN (180)";
    case e_path_shape::LAST_LEFT:
      return "e_path_shape::LAST_LEFT (90)";
    case e_path_shape::LAST_RIGHT:
      return "e_path_shape::LAST_RIGHT (270)";
    case e_path_shape::UP:
      return "e_path_shape::UP (360)";
    case e_path_shape::DOWN:
      return "e_path_shape::DOWN (540)";
    case e_path_shape::LEFT:
      return "e_path_shape::LEFT (630)";
    case e_path_shape::RIGHT:
      return "e_path_shape::RIGHT (450)";
    case e_path_shape::CORNER_RIGHT_UP:
      return "e_path_shape::CORNER_RIGHT_UP (720)";
    case e_path_shape::CORNER_UP_LEFT:
      return "e_path_shape::CORNER_UP_LEFT (990)";
    case e_path_shape::CORNER_LEFT_DOWN:
      return "e_path_shape::CORNER_LEFT_DOWN (900)";
    case e_path_shape::CORNER_DOWN_RIGHT:
      return "e_path_shape::CORNER_DOWN_RIGHT (810)";
    case e_path_shape::CORNER_UP_RIGHT:
      return "e_path_shape::CORNER_UP_RIGHT (1080)";
    case e_path_shape::CORNER_LEFT_UP:
      return "e_path_shape::CORNER_LEFT_UP (1350)";
    case e_path_shape::CORNER_DOWN_LEFT:
      return "e_path_shape::CORNER_DOWN_LEFT (1260)";
    case e_path_shape::CORNER_RIGHT_DOWN:
      return "e_path_shape::CORNER_RIGHT_DOWN (1170)";
    case e_path_shape::NONE:
      return "e_path_shape::NONE (no explicit value)";
    default:
      return "entry not matched";
  }
}


std::string e_direction_string(e_direction entry)
{
  switch (entry)
  {
    case e_direction::NONE:
      return "e_direction::NONE (0)";
    case e_direction::UP:
      return "e_direction::UP (360)";
    case e_direction::DOWN:
      return "e_direction::DOWN (540)";
    case e_direction::LEFT:
      return "e_direction::LEFT (630)";
    case e_direction::RIGHT:
      return "e_direction::RIGHT (450)";
    default:
      return "entry not matched";
  }
}


std::string e_unit_role_string(e_unit_role entry)
{
  switch (entry)
  {
    case e_unit_role::NONE:
      return "e_unit_role::NONE (0)";
    case e_unit_role::PASSENGER:
      return "e_unit_role::PASSENGER (no explicit value)";
    case e_unit_role::DRIVER:
      return "e_unit_role::DRIVER (no explicit value)";
    case e_unit_role::COPILOT:
      return "e_unit_role::COPILOT (no explicit value)";
    case e_unit_role::LOADER:
      return "e_unit_role::LOADER (no explicit value)";
    case e_unit_role::GUNNER:
      return "e_unit_role::GUNNER (no explicit value)";
    case e_unit_role::MECHANIC:
      return "e_unit_role::MECHANIC (no explicit value)";
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


std::string e_replay_mode_string(e_replay_mode entry)
{
  switch (entry)
  {
    case e_replay_mode::DEACTIVATED:
      return "e_replay_mode::DEACTIVATED (0)";
    case e_replay_mode::RECORD:
      return "e_replay_mode::RECORD (no explicit value)";
    case e_replay_mode::READ:
      return "e_replay_mode::READ (no explicit value)";
    default:
      return "entry not matched";
  }
}


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
    case e_input::EDIT_TERRAIN_NEXT:
      return "e_input::EDIT_TERRAIN_NEXT (no explicit value)";
    case e_input::EDIT_UNIT_NEXT:
      return "e_input::EDIT_UNIT_NEXT (no explicit value)";
    case e_input::EDIT_UNIT_DEL:
      return "e_input::EDIT_UNIT_DEL (no explicit value)";
    case e_input::NB_KEYS:
      return "e_input::NB_KEYS (no explicit value)";
    default:
      return "entry not matched";
  }
}


std::string e_key_string(e_key entry)
{
  switch (entry)
  {
    case e_key::SELECTION:
      return "e_key::SELECTION (no explicit value)";
    case e_key::SCREENSHOT:
      return "e_key::SCREENSHOT (no explicit value)";
    case e_key::DUMP_MAP:
      return "e_key::DUMP_MAP (no explicit value)";
    case e_key::QUICK_SAVE:
      return "e_key::QUICK_SAVE (no explicit value)";
    case e_key::QUICK_LOAD:
      return "e_key::QUICK_LOAD (no explicit value)";
    case e_key::TOGGLE_PANEL:
      return "e_key::TOGGLE_PANEL (no explicit value)";
    case e_key::EXIT:
      return "e_key::EXIT (no explicit value)";
    case e_key::UP:
      return "e_key::UP (no explicit value)";
    case e_key::DOWN:
      return "e_key::DOWN (no explicit value)";
    case e_key::LEFT:
      return "e_key::LEFT (no explicit value)";
    case e_key::RIGHT:
      return "e_key::RIGHT (no explicit value)";
    case e_key::EDIT_TERRAIN_NEXT:
      return "e_key::EDIT_TERRAIN_NEXT (no explicit value)";
    case e_key::EDIT_UNIT_NEXT:
      return "e_key::EDIT_UNIT_NEXT (no explicit value)";
    case e_key::EDIT_UNIT_DEL:
      return "e_key::EDIT_UNIT_DEL (no explicit value)";
    case e_key::NB_KEYS:
      return "e_key::NB_KEYS (no explicit value)";
    default:
      return "entry not matched";
  }
}


std::string e_option_argument_string(e_option_argument entry)
{
  switch (entry)
  {
    case e_option_argument::NONE:
      return "e_option_argument::NONE (0)";
    case e_option_argument::OPTIONAL:
      return "e_option_argument::OPTIONAL (no explicit value)";
    case e_option_argument::REQUIRED:
      return "e_option_argument::REQUIRED (no explicit value)";
    default:
      return "entry not matched";
  }
}


std::string e_resource_type_string(e_resource_type entry)
{
  switch (entry)
  {
    case e_resource_type::NONE:
      return "e_resource_type::NONE (0)";
    case e_resource_type::IMAGE:
      return "e_resource_type::IMAGE (no explicit value)";
    case e_resource_type::FONT:
      return "e_resource_type::FONT (no explicit value)";
    case e_resource_type::SOUND:
      return "e_resource_type::SOUND (no explicit value)";
    default:
      return "entry not matched";
  }
}


std::string e_entry_string(e_entry entry)
{
  switch (entry)
  {
    case e_entry::NONE:
      return "e_entry::NONE (0)";
    case e_entry::MOVE:
      return "e_entry::MOVE (no explicit value)";
    case e_entry::WAIT:
      return "e_entry::WAIT (no explicit value)";
    case e_entry::PICK_UP:
      return "e_entry::PICK_UP (no explicit value)";
    case e_entry::BOARD:
      return "e_entry::BOARD (no explicit value)";
    case e_entry::DROP_OFF:
      return "e_entry::DROP_OFF (no explicit value)";
    case e_entry::GET_OUT:
      return "e_entry::GET_OUT (no explicit value)";
    case e_entry::CREW:
      return "e_entry::CREW (no explicit value)";
    case e_entry::NEXT_TURN:
      return "e_entry::NEXT_TURN (no explicit value)";
    case e_entry::ATTACK:
      return "e_entry::ATTACK (no explicit value)";
    case e_entry::ENTER_BUILDING:
      return "e_entry::ENTER_BUILDING (no explicit value)";
    case e_entry::INVESTIGATE:
      return "e_entry::INVESTIGATE (no explicit value)";
    case e_entry::CONTROL:
      return "e_entry::CONTROL (no explicit value)";
    case e_entry::LEAVE:
      return "e_entry::LEAVE (no explicit value)";
    case e_entry::COLLECT:
      return "e_entry::COLLECT (no explicit value)";
    case e_entry::LOAD:
      return "e_entry::LOAD (no explicit value)";
    case e_entry::EXIT_BUILDING:
      return "e_entry::EXIT_BUILDING (no explicit value)";
    case e_entry::UNITS_BUILDING:
      return "e_entry::UNITS_BUILDING (no explicit value)";
    case e_entry::INVENTORY:
      return "e_entry::INVENTORY (no explicit value)";
    case e_entry::ITEM_USE:
      return "e_entry::ITEM_USE (no explicit value)";
    case e_entry::ITEM_COMBINE:
      return "e_entry::ITEM_COMBINE (no explicit value)";
    case e_entry::ITEM_MOVE:
      return "e_entry::ITEM_MOVE (no explicit value)";
    case e_entry::ITEM_DROP:
      return "e_entry::ITEM_DROP (no explicit value)";
    case e_entry::ITEM_EQUIP:
      return "e_entry::ITEM_EQUIP (no explicit value)";
    case e_entry::ITEM_UNEQUIP:
      return "e_entry::ITEM_UNEQUIP (no explicit value)";
    case e_entry::CANCEL:
      return "e_entry::CANCEL (no explicit value)";
    case e_entry::CONFIRM:
      return "e_entry::CONFIRM (no explicit value)";
    default:
      return "entry not matched";
  }
}


std::string e_panel_status_string(e_panel_status entry)
{
  switch (entry)
  {
    case e_panel_status::DEACTIVATED:
      return "e_panel_status::DEACTIVATED (0)";
    case e_panel_status::POSITION_LEFT:
      return "e_panel_status::POSITION_LEFT (no explicit value)";
    case e_panel_status::POSITION_RIGHT:
      return "e_panel_status::POSITION_RIGHT (no explicit value)";
    case e_panel_status::NB_PANEL_STATUS:
      return "e_panel_status::NB_PANEL_STATUS (no explicit value)";
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
    case e_state::SELECT_EXIT_ZONE:
      return "e_state::SELECT_EXIT_ZONE (no explicit value)";
    case e_state::BUILDING_MENU:
      return "e_state::BUILDING_MENU (no explicit value)";
    case e_state::BUILDING_UNITS:
      return "e_state::BUILDING_UNITS (no explicit value)";
    case e_state::INVENTORY:
      return "e_state::INVENTORY (no explicit value)";
    case e_state::ITEM_MENU:
      return "e_state::ITEM_MENU (no explicit value)";
    default:
      return "entry not matched";
  }
}

} // namespace debug
