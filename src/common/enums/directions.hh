/*
 * common/enums/directions.hh
 *
 *  Created on: July 21, 2013
 *      Author: Zermingore
 */

#ifndef ENUM_DIRECTIONS_HH_
# define ENUM_DIRECTIONS_HH_

/**
   * \brief stores vanilla directions
 * used for paths
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
