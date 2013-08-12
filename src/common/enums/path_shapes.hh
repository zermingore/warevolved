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
enum e_path_shape
{
  // Arrows (last of the path)
  E_PATH_SHAPE_LAST_UP = 0,
  E_PATH_SHAPE_LAST_DOWN = 180,
  E_PATH_SHAPE_LAST_LEFT = 90,
  E_PATH_SHAPE_LAST_RIGHT = 270,

  // Rectangles
  E_PATH_SHAPE_UP = 360,
  E_PATH_SHAPE_DOWN = 540, // same as UP
  E_PATH_SHAPE_LEFT = 630,
  E_PATH_SHAPE_RIGHT = 450, // same as LEFT

  // Corners (clockwise direction)
  E_PATH_SHAPE_CORNER_RIGHT_UP = 720,
  E_PATH_SHAPE_CORNER_UP_LEFT = 990,
  E_PATH_SHAPE_CORNER_LEFT_DOWN = 900,
  E_PATH_SHAPE_CORNER_DOWN_RIGHT = 810,

  // Same as above, just to help building the path
  E_PATH_SHAPE_CORNER_UP_RIGHT = 1080,
  E_PATH_SHAPE_CORNER_LEFT_UP = 1350,
  E_PATH_SHAPE_CORNER_DOWN_LEFT = 1260,
  E_PATH_SHAPE_CORNER_RIGHT_DOWN = 1170,

  E_PATH_NONE
};


#endif /* !PATH_SHAPES_HH_ */
