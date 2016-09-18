/**
  * \file
  * \date March 05, 2016
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
  // motion keys
  MOVE_UP_1 = 0,
  MOVE_UP_2,
  MOVE_DOWN_1,
  MOVE_DOWN_2,
  MOVE_LEFT_1,
  MOVE_LEFT_2,
  MOVE_RIGHT_1,
  MOVE_RIGHT_2,

  // action keys
  SELECTION_1,
  SELECTION_2,

  MENUBAR_1,
  MENUBAR_2,
  PANEL_1,
  PANEL_2,

  // exit requests
  EXIT_1,
  EXIT_2,


  NB_KEYS
};


#endif /* ENUM_INPUT_HH_ */
