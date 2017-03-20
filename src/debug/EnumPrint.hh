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

# include <debug/Debug.hh>
# include <common/enums/states.hh>


/// \todo static class

namespace debug {
  void printState(e_state state);
} // namespace debug


#endif /* !DEBUG_ENUM_PRINT_HH_ */
