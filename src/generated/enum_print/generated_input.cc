// auto-generated code, edit at your own risks
// generator: tools/code_generation/enum_print/generate_enum_print.sh
// generated on: Do Apr 13 07:34:09 CEST 2017


#include <string>
#include <common/enums/input.hh>

namespace debug {

std::string e_input_string(e_input entry);

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
    case e_input::EXIT:
      return "e_input::EXIT (no explicit value)";
    case e_input::NB_KEYS:
      return "e_input::NB_KEYS (no explicit value)";
    default:
      return "entry not matched";
  }
}

} // namespace debug
