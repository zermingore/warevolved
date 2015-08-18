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
enum class direction
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

#endif /* DIRECTIONS_HH_ */
