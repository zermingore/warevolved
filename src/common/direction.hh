/*
 * direction.hh
 *
 *  Created on: Jul 21, 2013
 *      Author: Zermingore
 */

#ifndef DIRECTION_HH_
# define DIRECTION_HH_

/** \brief stores vanilla directions
 ** used for paths
 */
enum e_direction
{
  E_DIRECTION_NONE = 0,

  // these values matches rotation angle
  // (sprites are always oriented to the top
  //   rotation are done in trigonometric direction)
  E_DIRECTION_UP = 360,
  E_DIRECTION_DOWN = 540,
  E_DIRECTION_LEFT = 450,
  E_DIRECTION_RIGHT = 630
};

#endif /* DIRECTION_HH_ */
