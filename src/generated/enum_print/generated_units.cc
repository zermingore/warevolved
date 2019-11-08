// auto-generated code, edit at your own risks
// generator: tools/code_generation/enum_print/generate_enum_print.sh
// generated on: Sat Nov  2 11:42:23 CET 2019


#include <common/enums/units.hh>
#include <string>

namespace debug {

std::string e_unit_string(e_unit entry);

std::string e_unit_string(e_unit entry)
{
  switch (entry)
  {
    case e_unit::SOLDIER:
      return "e_unit::SOLDIER (0)";
    case e_unit::CAR:
      return "e_unit::CAR (no explicit value)";
    case e_unit::NB_UNITS:
      return "e_unit::NB_UNITS (no explicit value)";
    case e_unit::NONE:
      return "e_unit::NONE (no explicit value)";
    default:
      return "entry not matched";
  }
}

} // namespace debug
