/**
 * \file
 * \date March 5, 2016
 * \author Zermingore
 */

#ifndef ENUM_INPUT_HH_
# define ENUM_INPUT_HH_


/**
 * \enum input
 * \brief Logical input names.
 */
enum class e_input
{
  // Motion keys
  MOVE_UP = 0,
  MOVE_DOWN,
  MOVE_LEFT,
  MOVE_RIGHT,

  // Action keys
  SELECTION,

  // Interface keys
  TOGGLE_PANEL,

  // Global inputs
  SCREENSHOT,

  // Exit requests
  EXIT,

  NB_KEYS
};


#endif /* ENUM_INPUT_HH_ */
