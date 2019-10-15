// auto-generated code, edit at your own risks
// generator: tools/code_generation/enum_print/generate_enum_print.sh
// generated on: Mon Oct 14 18:46:42 CEST 2019


#include <string>
#include <common/enums/path_shapes.hh>

namespace debug {

std::string e_path_shape_string(e_path_shape entry);

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

} // namespace debug
