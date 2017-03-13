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
  // motion keys
  MOVE_UP = 0,
  MOVE_DOWN,
  MOVE_LEFT,
  MOVE_RIGHT,

  // action keys
  SELECTION,

  // exit requests
  EXIT,

  NB_KEYS
};


#endif /* ENUM_INPUT_HH_ */
