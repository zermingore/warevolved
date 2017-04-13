// auto-generated code, edit at your own risks
// generator: tools/code_generation/enum_print/generate_enum_print.sh
// generated on: Do Apr 13 07:34:09 CEST 2017


#include <string>
#include <common/enums/directions.hh>

namespace debug {

std::string e_direction_string(e_direction entry);

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

} // namespace debug
