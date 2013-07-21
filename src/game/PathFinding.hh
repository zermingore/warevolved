/*
 * PathFinding.hh
 *
 *  Created on: Jul 18, 2013
 *      Author: Zermingore
 */

#ifndef PATHFINDING_HH_
# define PATHFINDING_HH_

# include <common/path_shape.hh>
# include <resources/Image.hh>
# include <game/PathElement.hh>


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

  // TODO remove vector, only use PathElement class
  std::vector<PathElement*> _graphicPath; ///< path elements array
};

#endif /* !PATHFINDING_HH_ */
