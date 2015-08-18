/*
 * common/enums/path_shapes.hh
 *
 *  Created on: July 21, 2013
 *      Author: Zermingore
 */

#ifndef PATH_SHAPES_HH_
# define PATH_SHAPES_HH_


/** \enum Help matching which element we want to display,
 **   drawing the path
 ** Their values matches the needed sprite rotation
 */
enum class path_shape
{
  // Arrows (last of the path)
  LAST_UP = 0,
  LAST_DOWN = 180,
  LAST_LEFT = 90,
  LAST_RIGHT = 270,

  // Rectangles
  UP = 360,
  DOWN = 540, // same as UP
  LEFT = 630,
  RIGHT = 450, // same as LEFT

  // Corners (clockwise direction)
  CORNER_RIGHT_UP = 720,
  CORNER_UP_LEFT = 990,
  CORNER_LEFT_DOWN = 900,
  CORNER_DOWN_RIGHT = 810,

  // Same as above, just to help building the path
  CORNER_UP_RIGHT = 1080,
  CORNER_LEFT_UP = 1350,
  CORNER_DOWN_LEFT = 1260,
  CORNER_RIGHT_DOWN = 1170,

  NONE
};


#endif /* !PATH_SHAPES_HH_ */
