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
  NONE = 0,         ///< we should never be in this state

  GLOBAL,           ///< Default state, handling inputs accessible everywhere

  PLAYING,          ///< Browsing the map
  MAP_MENU,         ///< Generic map menu: next turn, ...

  SELECTION_UNIT,   ///< Pick a Unit
  MOVING_UNIT,      ///< Move it
  ACTION_MENU,      ///< Give it an order (confirm move, switch to attack state)
  CREW_MANAGEMENT,  ///< Manage a Vehicle crew

  SELECTION_CREW,   ///< Select a member in a Unit crew

  SELECT_TARGET,    ///< Select a taget (attack, heal, ...)
  SELECT_DROP_ZONE, ///< Select a taget (attack, heal, ...)
};



#endif /* !ENUM_STATES_HH_ */
