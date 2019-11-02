/**
 * \date November 02, 2019
 * \author tools/code_generation/enum_print/generate_enum_print.sh
 * \brief Prototypes used to print the enums values
 * \note generated by tools/code_generation/enum_print/generate_enum_print.sh
 */


#ifndef GENERATED_ENUM_PRINT_PROTOTYPES_HH_
# define GENERATED_ENUM_PRINT_PROTOTYPES_HH_

# include <string>
# include <common/enums/units.hh>
# include <common/enums/terrains.hh>
# include <common/enums/path_shapes.hh>
# include <common/enums/attack_result.hh>
# include <common/enums/directions.hh>
# include <common/enums/states.hh>
# include <common/enums/input.hh>


namespace debug {

std::string e_unit_string(e_unit entry);
std::string e_terrain_string(e_terrain entry);
std::string e_path_shape_string(e_path_shape entry);
std::string e_attack_result_string(e_attack_result entry);
std::string e_direction_string(e_direction entry);
std::string e_state_string(e_state entry);
std::string e_input_string(e_input entry);

} // namespace debug


#endif /* !GENERATED_ENUM_PRINT_PROTOTYPES_HH_ */
