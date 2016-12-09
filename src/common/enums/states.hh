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
  NONE = 0, // we should never be in this state

  MENU,
  PLAYING,

  SELECTION_UNIT, // pick a Unit
  MOVING_UNIT,    // move it
  ACTION_MENU,    // give it an order (confirm move, switch to attack state)
  ATTACK,         // ask a Unit to attack
};


#endif /* !ENUM_STATES_HH_ */
