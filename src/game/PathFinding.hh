/*
 * PathFinding.hh
 *
 *  Created on: Jul 18, 2013
 *      Author: Zermingore
 */

#ifndef PATHFINDING_HH_
# define PATHFINDING_HH_

# include <vector>
# include <common/enums/path_shape.hh>
# include <common/enums/direction.hh>
# include <resources/Image.hh>


/** \brief Computes and display path findings
 */
class PathFinding
{
public:
  /** \brief Constructor
   */
  PathFinding();

  /** \brief Destructor
   */
  ~PathFinding();

  /** \brief sets the origin of the path
   **   also updates _current position
   */
  void setOrigin(unsigned int x, unsigned int y);


  /** \brief current path length getter
   */
  unsigned int getCurrentLength();

  /** \brief current path length setter
   */
  void setCurrentLength(const unsigned int length);

  /** \brief Maximum path length getter
   */
  unsigned int getMaxLength();

  /** \brief Maximum path length setter
   */
  void setMaxLength(const unsigned int length);

  /** \brief allowed move notifier
   ** \return true if the move is allowed
   */
  bool allowedMove(); // TODO send direction request

  /** \brief adds the next element to the current path
   ** \param direction of the element
   */
  void addNextDirection(e_direction direction);

  /** \brief uses _graphicPath to draw the current path
   */
  void drawPath();

  /** \brief clears current path
   ** calls deleteImagesVector, freeing images
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

  bool _cached; ///< true if we have already build the path

  unsigned int _maxLength; ///< path max length
  unsigned int _currentLength; ///< path current length

  std::vector<e_direction> _directions; ///< list of path directions
                                        ///< filled through addNextDirection

  std::vector<Image*> _images; ///< Images* of the path vector
};

#endif /* !PATHFINDING_HH_ */
