/*
 * PathFinding.hh
 *
 *  Created on: Jul 18, 2013
 *      Author: Zermingore
 */

#ifndef PATHFINDING_HH_
# define PATHFINDING_HH_

# include <resources/Image.hh>

/** \brief enum to help matching which element we want to display,
 **   drawing the path
 ** Their values matches the needed sprite rotation
 */
enum e_path_shape
{
  // Arrows
  E_PATH_SHAPE_LAST_UP = 0,
  E_PATH_SHAPE_LAST_DOWN = 180,
  E_PATH_SHAPE_LAST_LEFT = 90,
  E_PATH_SHAPE_LAST_RIGHT = 270,

  // Rectangles
  E_PATH_SHAPE_UP = 360,
  E_PATH_SHAPE_DOWN = 540, // same as UP
  E_PATH_SHAPE_LEFT = 450,
  E_PATH_SHAPE_RIGHT = 630, // same as LEFT

  // Corners (trigonometric direct)
  E_PATH_SHAPE_CORNER_RIGHT_UP = 720,
  E_PATH_SHAPE_CORNER_UP_LEFT = 810,
  E_PATH_SHAPE_CORNER_LEFT_DOWN = 900,
  E_PATH_SHAPE_CORNER_DOWN_RIGHT = 990,

  // Same as above, just to help building the path
  E_PATH_SHAPE_CORNER_UP_RIGHT = 1080,
  E_PATH_SHAPE_CORNER_LEFT_UP = 1170,
  E_PATH_SHAPE_CORNER_DOWN_LEFT = 1260,
  E_PATH_SHAPE_CORNER_RIGHT_DOWN = 1350
};

/** \brief Computes and display path findings
 */
class PathFinding
{
public:
  /** Default Ctor
   */
  PathFinding();

  /** Destructor
   */
  ~PathFinding();

  /** \brief uses _graphicPath to draw the current path
   */
  void drawPath();


private:
  /** \brief returns the sprite matching e_path_shape
   ** does the rotation if needed
   ** \return the image matching e_path_shape
   */
  Image *getImage(e_path_shape shape);

  std::vector<e_path_shape> _graphicPath; ///< path elements array
};

#endif /* PATHFINDING_HH_ */
