/*
 * PathElement.hh
 *
 *  Created on: Jul 21, 2013
 *      Author: Zermingore
 */

#ifndef PATHELEMENT_HH_
# define PATHELEMENT_HH_

# include <common/path_shape.hh>


// TODO optimize this path management
//   could use a list
//     store first element and it's orientation
//     direction of the following elements (could use a byte 1-4)

/** \brief class for path-finding elements
 */
class PathElement
{
public:
  PathElement();

  // dummy version Ctor
  PathElement(unsigned int x, unsigned int y, e_path_shape shape);

  /** Destructor */
  ~PathElement();

  /** \brief _x getter */
  unsigned int getX();

  /** \brief _y getter */
  unsigned int getY();

  /** \brief shape getter */
  inline e_path_shape getShape() {return _shape;};

  // TODO addNext()

private:
  // TODO origin (avoid using selected cell)

  unsigned int _x; ///< cell x coordinate
  unsigned int _y; ///< cell y coordinate
  e_path_shape _shape; ///< path shape
};

#endif /* !PATHELEMENT_HH_ */
