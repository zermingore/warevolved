/**
 * \file
 * \date July 18, 2013
 * \author Zermingore
 */

#ifndef PATHFINDING_HH_
# define PATHFINDING_HH_

# include <vector>
# include <memory>
# include <structures/Vector.hh>
# include <resources/Sprite.hh>

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
   * \brief _enemyPositions getter
   * \return a pointer on the vector of enemy positions
   */
  static std::shared_ptr<std::vector<std::shared_ptr<Cell>>> getEnemyPositions() {
    return std::make_shared<std::vector<std::shared_ptr<Cell>>> (_enemyPositions);
  }

  /**
   * \brief allowed move notifier
   * \param direction direction towards the next cell
   * \return true if the move is allowed
   * \note The map border checking must be done outside
   */
  static bool allowedMove(e_direction direction);

  /**
   * \brief adds the next element to the current path
   * \param direction direction of the element
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
  auto unit() { return _unit; }

  /**
   * \brief releases (reset) _unit
   */
  static void removeUnit() { _unit.reset(); }

  /**
   * \brief Sets cells highlight as follow:
   * - Highlight reachable cells (at moving range)
   * - Highlight enemy units at shooting range
   * - Highlight friendly units at moving range
   */
  static void highlightCells();

  /**
   * \brief compute and return list of available targets
   * \param unit Unit used as attacker
   * \param cell coordinates from where to get the targets
   */
  static std::shared_ptr<std::vector<std::shared_ptr<Cell>>>
  getTargets(std::shared_ptr<Unit> unit, std::shared_ptr<Cell> cell);


private:
  /**
   * \brief returns the sprite matching e_path_shape
   * does the rotation if needed
   * \return the image matching e_path_shape
   */
  static std::shared_ptr<resources::Sprite> getSprite(size_t index);

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


  /**
   * \brief returns the Manhattan distance between two cells
   * \param a first cell
   * \param b second cell
   * \return the distance between the two cells
   */
  static size_t manhattan(Coords a, Coords b);


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
  static std::vector<std::shared_ptr<resources::Sprite>> _images;

  ///< list of reachable cells for the selected unit
  static std::vector<std::shared_ptr<Cell>> _reachableCells;

  ///< list of cells occupied by an enemy unit
  static std::vector<std::shared_ptr<Cell>> _enemyPositions;
};


#endif /* !PATHFINDING_HH_ */
