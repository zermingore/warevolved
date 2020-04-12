// auto-generated code, edit at your own risks
// generator: ./generate_enum_print.sh
// generated on: Sun Apr 12 19:51:46 CEST 2020


#include <string>
#include <common/enums/attack_result.hh>

namespace debug {

std::string e_attack_result_string(e_attack_result entry);

std::string e_attack_result_string(e_attack_result entry)
{
  switch (entry)
  {
    case e_attack_result::INVALID:
      return "e_attack_result::INVALID (0)";
    case e_attack_result::NONE_DIED:
      return "e_attack_result::NONE_DIED (no explicit value)";
    case e_attack_result::ATTACKER_DIED:
      return "e_attack_result::ATTACKER_DIED (no explicit value)";
    case e_attack_result::DEFENDER_DIED:
      return "e_attack_result::DEFENDER_DIED (no explicit value)";
    case e_attack_result::BOTH_DIED:
      return "e_attack_result::BOTH_DIED (no explicit value)";
    default:
      return "entry not matched";
  }
}

} // namespace debug
