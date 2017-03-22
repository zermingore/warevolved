/**
 * \file
 * \date January 13, 2017
 * \author Zermingore
 */

#ifndef DEBUG_ENUM_PRINT_HH_
# define DEBUG_ENUM_PRINT_HH_


# ifndef DEBUG
#   error "abort, should not be compiled in release"
# endif

# include <string>
# include <debug/Debug.hh>
# include <common/enums/states.hh>
# include <common/enums/input.hh>


/// \todo static class

namespace debug {
  void printState(e_state state);

  std::string printInput(e_input input);
} // namespace debug


#endif /* !DEBUG_ENUM_PRINT_HH_ */
