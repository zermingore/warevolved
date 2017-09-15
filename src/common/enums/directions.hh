/**
 * \file
 * \date July 21, 2013
 * \author Zermingore
 */

#ifndef ENUM_DIRECTIONS_HH_
# define ENUM_DIRECTIONS_HH_


/**
 * \enum e_direction
 * \brief Stores vanilla directions. Used for paths
 */
enum class e_direction
{
  NONE = 0,

  // these values matches rotation angle
  // (sprites are always oriented to the top
  //   rotation are done in clockwise direction)
  UP = 360,
  DOWN = 540,
  LEFT = 630,
  RIGHT = 450
};

#endif /* ENUM_DIRECTIONS_HH_ */
