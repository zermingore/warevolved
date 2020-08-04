// auto-generated code, edit at your own risks
// generator: generate_enum_print.sh
// generated on: Tue 04 Aug 2020 05:38:27 PM CEST



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

} // namespace debug
