// auto-generated code, edit at your own risks
// generator: tools/code_generation/enum_print/generate_enum_print.sh
// generated on: Sat Nov  2 11:42:23 CET 2019


#include <common/enums/terrains.hh>
#include <string>

namespace debug {

std::string e_terrain_string(e_terrain entry);

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

} // namespace debug
