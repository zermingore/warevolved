/*
 * game/PathFinding.hh
 *
 *  Created on: July 18, 2013
 *      Author: Zermingore
 */

#ifndef PATHFINDING_HH_
# define PATHFINDING_HH_

# include <vector>
# include <common/enums/path_shapes.hh>
# include <common/enums/directions.hh>
# include <game/units/Unit.hh>
# include <resources/Image.hh>
# include <game/Cell.hh>


/** \class PathFinding Computes and display path findings
 **   as reachable cells and possible targets for the selected unit
 ** It display user's path input and check it's validity
 */
class PathFinding
{
public:
  /** \brief Constructor
   */
  PathFinding();

  /** \brief Destructor
   */
  ~PathFinding() { deleteImagesVector(); }

  /** \brief sets the origin of the path
   **   also updates _current position
   */
  void setOrigin(Coords coords);

  /** \brief allowed move notifier
   ** \return true if the move is allowed
   */
  inline bool allowedMove() // TODO send direction request
  { return _currentLength < _maxLength; }

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

  /** \brief hides crossable cells
   */
  void hideAllowedPath() const;

  /** \brief current Unit (_unit) getter
   ** \return _unit
   */
  std::shared_ptr<Unit> unit() { return _unit; }

  /** \brief releases (reset) _unit
   */
  void removeUnit() { _unit.reset(); }

private:
  /** \brief returns the sprite matching e_path_shape
   ** does the rotation if needed
   ** \return the image matching e_path_shape
   */
  Image getImage(unsigned int index);

  /** \brief builds Images* Vector (_images)
   */
  void buildImageVector(); // TODO use (cache management)

  /** \brief clears _images Vector
   */
  inline void deleteImagesVector() { _images.clear(); }

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

  /** \brief Highlights cells which selected unit (_unit) can cross
   ** (uses a Flood Fill algorithm)
   */
  void showAllowedPath();

  /** \brief sets highlight and highlight color for reachable cells
   */
  void highlightCells();


  std::shared_ptr<Unit> _unit; ///< The selected Unit we're working with
  Coords _origin; ///< origin cell coordinates
  Coords _current; ///< current cell coordinates
  int _maxLength; ///< path max length
  int _currentLength; ///< path current length

  ///< list of path directions filled through addNextDirection
  std::vector<e_direction> _directions;
  std::vector<Image> _images; ///< Images of the path vector

  ///< list of reachable cells for the selected unit
  std::vector<std::shared_ptr<Cell>> _reachableCells;
};

#endif /* !PATHFINDING_HH_ */
