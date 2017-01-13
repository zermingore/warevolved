/**
 * \file
 * \date July 24, 2013
 * \author Zermingore
 */

#ifndef ENUM_STATES_HH_
# define ENUM_STATES_HH_


/**
 * \enum e_state
 * \brief various menu state values. Used to notify the state stack.
 */
enum class e_state: int
{
  NONE = 0,          // we should never be in this state

  MENU,              // Browsing a menu
  PLAYING,           // Browsing the map

  SELECTION_UNIT,    // Pick a Unit
  MOVING_UNIT,       // Move it
  ACTION_MENU,       // Give it an order (confirm move, switch to attack state)

  COMMANDING_UNIT,   // Selecting the order to give to the unit
  SELECTING_TARGET,  // Select a taget (attack, heal, ...)
};



#endif /* !ENUM_STATES_HH_ */
