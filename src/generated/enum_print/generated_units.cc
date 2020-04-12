// auto-generated code, edit at your own risks
// generator: ./generate_enum_print.sh
// generated on: Sun Apr 12 19:51:46 CEST 2020


#include <string>
#include <common/enums/units.hh>

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
