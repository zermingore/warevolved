/*
 * PathFinding.hh
 *
 *  Created on: Jul 18, 2013
 *      Author: Zermingore
 */

#ifndef PATHFINDING_HH_
# define PATHFINDING_HH_

# include <vector>
# include <common/path_shape.hh>
# include <common/direction.hh>
# include <resources/Image.hh>


/** \brief Computes and display path findings
 */
class PathFinding
{
public:
  /** Constructor
   */
  PathFinding(unsigned int x, unsigned int y);

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

  /** \brief clears current path
   */
  void clearPath();


private:
  /** \brief returns the sprite matching e_path_shape
   ** does the rotation if needed
   ** \return the image matching e_path_shape
   */
  Image *getImage(unsigned int index);

  /** \brief builds Images* Vector (_images)
   */
  void buildImageVector(); // TODO use (cache management)

  /** \brief frees Images* Vector (_images)
   ** deletes all Images in _images
   */
  void deleteImagesVector();

  /** \brief updates current cell coordinates
   **   according to \param direction
   ** \param direction current move direction
   */
  void updateCurrentCell(e_direction direction);

  /** \brief returns shape matching _direction[\param index]
   ** \param index index in _direction vector
   ** \return shape of _direction[\param index]
   **   according to the next direction (for smooth corners)
   */
  e_path_shape getShape(unsigned int index);


  unsigned int _originX; ///< origin cell x coordinate
  unsigned int _originY; ///< origin cell y coordinate

  unsigned int _currentX; ///< current cell x coordinate
  unsigned int _currentY; ///< current cell y coordinate

  std::vector<e_direction> _directions; ///< list of path directions
                                        ///< filled through addNextDirection

  std::vector<Image*> _images; ///< Images* of the path vector
};

#endif /* !PATHFINDING_HH_ */
