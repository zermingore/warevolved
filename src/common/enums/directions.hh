/*
 * common/enums/directions.hh
 *
 *  Created on: July 21, 2013
 *      Author: Zermingore
 */

#ifndef DIRECTIONS_HH_
# define DIRECTIONS_HH_

/** \brief stores vanilla directions
 ** used for paths
 */
enum e_direction
{
  E_DIRECTION_NONE = 0,

  // these values matches rotation angle
  // (sprites are always oriented to the top
  //   rotation are done in clockwise direction)
  E_DIRECTION_UP = 360,
  E_DIRECTION_DOWN = 540,
  E_DIRECTION_LEFT = 630,
  E_DIRECTION_RIGHT = 450
};

#endif /* DIRECTIONS_HH_ */
