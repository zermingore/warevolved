// auto-generated code, edit at your own risks
// generator: tools/code_generation/enum_print/generate_enum_print.sh
// generated on: Mon Oct 14 18:46:42 CEST 2019


#include <string>
#include <common/enums/panel_status.hh>

namespace debug {

std::string e_panel_status_string(e_panel_status entry);

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

} // namespace debug
