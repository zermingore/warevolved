/*
 * PathFinding.hh
 *
 *  Created on: Jul 18, 2013
 *      Author: Zermingore
 */

#ifndef PATHFINDING_HH_
# define PATHFINDING_HH_

# include <list>
# include <common/path_shape.hh>
# include <common/direction.hh>
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

  /** \brief shape getter
   ** checks the both previous and next segments
   **   to return the right match
   */
  e_path_shape getShape();

  /** \brief adds the next element to the current path
   ** \param direction of the element
   */
  void addNextDirection(e_direction direction);



  /** \brief uses _graphicPath to draw the current path
   */
  void drawPath();


private:
  /** \brief returns the sprite matching e_path_shape
   ** does the rotation if needed
   ** \return the image matching e_path_shape
   */
  Image *getImage(unsigned int index);

  // TODO remove vector, only use PathElement class
  //std::vector<PathElement*> _graphicPath; ///< path elements array

  // path direction list
  // list[0]: origin cell
  // list[i]: relative to list[i-1]
//  std::list<e_direction> _directions;

  void buildImageList();
  e_path_shape getShape(unsigned int index);


  unsigned int _originX; ///< origin cell x coordinate
  unsigned int _originY; ///< origin cell y coordinate

  unsigned int _currentX; ///< current cell x coordinate
  unsigned int _currentY; ///< current cell y coordinate

  unsigned int _index; ///< _directions list current index

  std::vector<e_direction> _directions; ///< list of path directions
                                      ///< filled through addNextDirection

};

#endif /* !PATHFINDING_HH_ */
