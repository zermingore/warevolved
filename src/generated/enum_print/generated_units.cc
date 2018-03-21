// auto-generated code, edit at your own risks
// generator: tools/code_generation/enum_print/generate_enum_print.sh
// generated on: Mi Mär 21 18:22:27 CET 2018


#include <string>
#include <common/enums/units.hh>

namespace debug {

std::string e_unit_string(e_unit entry);

std::string e_unit_string(e_unit entry)
{
  switch (entry)
  {
    case e_unit::SOLDIERS:
      return "e_unit::SOLDIERS (0)";
    case e_unit::NB_UNITS:
      return "e_unit::NB_UNITS (no explicit value)";
    case e_unit::NONE:
      return "e_unit::NONE (no explicit value)";
    default:
      return "entry not matched";
  }
}

} // namespace debug
