// auto-generated code, edit at your own risks
// generator: ./generate_enum_print.sh
// generated on: Sun Apr 12 19:51:46 CEST 2020


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
