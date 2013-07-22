/*
 * PathElement.hh
 *
 *  Created on: Jul 21, 2013
 *      Author: Zermingore
 */

#ifndef PATHELEMENT_HH_
# define PATHELEMENT_HH_

# include <common/path_shape.hh>
# include <common/direction.hh>


// TODO optimize this path management
//   could use a list
//     store first element and it's orientation
//     direction of the following elements (could use a byte 1-4)

/** \brief class for path-finding elements
 ** this class does not compute the path, it just stores it
 */
class PathElement
{
public:
  /** \brief Constructor
   ** sets the origin cell
   ** it's orientation will be computed as soon as we'll get another element
   */
  PathElement(unsigned int x, unsigned int y);

  /** Destructor */
  ~PathElement();

  /** \brief current cell x coordinate getter */
  unsigned int getX();

  /** \brief current cell y coordinate getter */
  unsigned int getY();

  /** \brief shape getter
   ** checks the both previous and next segments
   **   to return the right match
   */
  e_path_shape getShape();

  /** \brief adds the next element to the current path
   ** \param direction of the element
   **   as the path finding is computed elsewhere,
   **   we have not to check it
   */
  void addNextDirection(e_direction direction);


private:
  unsigned int _x; ///< cell x coordinate
  unsigned int _y;

  e_path_shape _shape;
  Image *_image;

//  unsigned int _originX; ///< origin cell x coordinate
//  unsigned int _originY; ///< origin cell y coordinate
//
//  unsigned int _currentX; ///< current cell x coordinate
//  unsigned int _currentY; ///< current cell y coordinate
//
//  unsigned int _index; ///< _directions list current index
//
//  std::list<e_direction> _directions; ///< list of path directions
//                                      ///< filled through addNextDirection
};

#endif /* !PATHELEMENT_HH_ */
