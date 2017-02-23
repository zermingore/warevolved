/**
 * \file
 * \date July 18, 2013
 * \author Zermingore
 */

#ifndef PATHFINDING_HH_
# define PATHFINDING_HH_

# include <vector>
# include <memory>
# include <common/structures/Vector.hh>
# include <resources/Image.hh>

class Map;
class Unit;
class Cell;

enum class e_direction;
enum class e_path_shape;


/**
 * \class PathFinding
 * \brief Computes and display found path.
 *
 * Display reachable cells and possible targets for the selected unit.
 * Display user's path input and check it's validity.
 */
class PathFinding
{
public:
  /**
   * \brief _map setter
   */
  static void setMap(std::shared_ptr<Map> map) { _map = map; }

  /**
   * \brief sets the origin of the path
   *   also updates _current position
   */
  static void setOrigin(Coords coords, std::shared_ptr<Unit> unit);

  /**
   * \brief allowed move notifier
   * \return true if the move is allowed
   */
  static bool allowedMove();

  /**
   * \brief allowed attack notifier
   * \param unit Attacking unit
   * \param c cell from which the unit attacks
   * \return true if the unit can attack from coordinates (false otherwise)
   */
  static bool allowedAttack(std::shared_ptr<Unit> unit, Coords c);

  /**
   * \brief adds the next element to the current path
   * \param direction of the element
   */
  static void addNextDirection(e_direction direction);

  /**
   * \brief uses _graphicPath to draw the current path
   */
  static void drawPath();

  /**
   * \brief clears current path
   * calls deleteImagesVector, freeing images
   */
  static void clearPath();

  /**
   * \brief hides crossable cells
   */
  static void hideAllowedPath();

  /**
   * \brief current Unit (_unit) getter
   * \return _unit
   */
  std::shared_ptr<Unit> unit() { return _unit; }

  /**
   * \brief releases (reset) _unit
   */
  static void removeUnit() { _unit.reset(); }

  /**
   * \brief Highlights cells which selected unit (_unit) can cross.
   * (uses a Flood Fill algorithm)
   */
  static void showAllowedPath();


private:
  /**
   * \brief returns the sprite matching e_path_shape
   * does the rotation if needed
   * \return the image matching e_path_shape
   */
  static std::shared_ptr<resources::Image> getImage(size_t index);

  /**
   * \brief builds Images* Vector (_images)
   */
  static void buildImageVector();  /// \todo use (cache management)

  /**
   * \brief clears _images Vector
   */
  static void deleteImagesVector() { _images.clear(); }

  /**
   * \brief updates current cell coordinates
   *   according to \param direction
   * \param direction current move direction
   */
  static void updateCurrentCell(e_direction direction);

  /**
   * \brief returns shape matching _direction (index parameter)
   * \param index index in _direction vector.
   * \return shape of _direction[\param index]
   *   according to the next direction (for smooth corners).
   */
  static e_path_shape getShape(size_t index);


  /// Sets highlight and highlight color for reachable cells.
  static void highlightCells();

  /// \todo make a relation map - path-finding
  static std::shared_ptr<Map> _map;   ///< Map of the battle.
  static std::shared_ptr<Unit> _unit; ///< The selected Unit.

  static Coords _origin;  ///< Origin cell coordinates.
  static Coords _current; ///< Current cell coordinates.

  static size_t _maxLength;     ///< Path max length.
  static size_t _currentLength; ///< Path current length.

  ///< List of path directions filled through addNextDirection.
  static std::vector<e_direction> _directions;

  ///< Images of the path vector.
  static std::vector<std::shared_ptr<resources::Image>> _images;

  ///< list of reachable cells for the selected unit
  static std::vector<std::shared_ptr<Cell>> _reachableCells;

  ///< list of cells occupied by an enemy unit
  static std::vector<std::shared_ptr<Cell>> _enemyPositions;
};


#endif /* !PATHFINDING_HH_ */
