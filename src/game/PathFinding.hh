/**
 * \file
 * \date July 18, 2013
 * \author Zermingore
 * \brief PathFinding class declarations
 *   and enums e_path_shape e_directions definitions
 */

#ifndef PATH_FINDING_HH_
# define PATH_FINDING_HH_

# include <mutex>
# include <vector>
# include <memory>
# include <structures/Vector.hh>
# include <graphics/Sprite.hh>

class Map;
class Unit;
class Cell;

enum class e_path_shape; // definition follows
enum class e_direction;  // definition follows



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
   * \brief Deleted default constructor: The origin is required
   */
  PathFinding() = delete;

  /**
   * \brief Instantiate a PathFinding based on the given origin unit
   * \param origin Unit origin of the path
   * \note Throws if the given Unit is NULL
   */
  explicit PathFinding(const std::shared_ptr<Unit>& origin);

  /**
   * \brief Default destructor
   */
  ~PathFinding() = default;


  /**
   * \brief allowed move notifier
   * \param direction direction towards the next cell
   * \return true if the move is allowed
   * \note The map border checking must be done outside
   */
  bool allowedMove(e_direction direction);

  /**
   * \brief adds the next element to the current path
   * \param direction direction of the element
   */
  void addNextDirection(e_direction direction);

  /**
   * \brief uses _graphicPath to draw the current path
   * \note While this method runs, a call to addNextDirection() can be executed
   */
  void drawPath();

  /**
   * \brief Sets cells highlight as follow:
   * - Highlight reachable cells (at moving range)
   * - Highlight enemy units at shooting range
   * - Highlight friendly units at moving range
   */
  void highlightCells();

  /**
   * \brief hides crossable cells, targets and friendly units
   * \note clears cells' _highlight flag
   */
  void hideAllowedPath();

  /**
   * \brief Return the list of available targets
   * \param ref Unit for which and from where the targets will be seek
   * \param coords Coordinates where the attacker is located
   * \return List of cells containing a target
   */
  std::shared_ptr<std::vector<std::shared_ptr<Cell>>> getTargets(
    const std::shared_ptr<const Unit>& ref, const Coords& coords) const;

  /**
   * \brief Return the list of available drop locations
   * \param coords Coordinates where the vehicle is located
   * \return List of valid drop zones
   */
  std::vector<std::shared_ptr<const Cell>>
  getDropZones(const Coords& coords) const;



private:
  /**
   * \brief Compute and store the costs to every cell
   * \note Unreachable cells have a cost of motion + range + 1
   */
  void computeCosts();

  /**
   * \brief returns the sprite matching e_path_shape
   * does the rotation if needed
   * \return the image matching e_path_shape
   */
  std::shared_ptr<graphics::Sprite> getSprite(size_t index);

  /**
   * \brief updates current cell coordinates according to direction
   * \param direction current move direction
   */
  void updateCurrentCell(e_direction direction);

  /**
   * \brief returns shape matching _direction (index parameter)
   * \param index index in _direction vector.
   * \return shape of _direction[index]
   *   according to the next direction (for smooth corners).
   */
  e_path_shape getShape(size_t index) const;

  /**
   * \brief returns the Manhattan distance between two cells
   * \param a first cell
   * \param b second cell
   * \return the distance (in cells) between the two cells
   */
  size_t manhattan(const Coords a, const Coords b) const;

  /**
   * \brief Get the list of valid adjacent cells
   * \param coords Coordinates of the cell from where to check
   * \return List of valid adjacent cells on the map
   */
  std::vector<std::shared_ptr<const Cell>>
  getAdjacentCells(const Coords coords) const;



  std::shared_ptr<Unit> _origin;  ///< Unit at the origin of the path
  Coords _current;                ///< Current cell coordinates.
  Coords _lastPosition;           ///< Last position of the path

  size_t _maxLength;     ///< Path max length.
  size_t _currentLength; ///< Path current length.

  std::vector<std::vector<size_t>> _costs; ///< Cost values to reach every cell

  std::shared_ptr<Map> _map; ///< Do not access Battle all the time

  /// List of path directions filled through addNextDirection.
  std::vector<e_direction> _directions;

  std::mutex _lockDirections; ///< Locking _directions while pushing back

  /// list of reachable cells for the selected unit
  std::vector<std::shared_ptr<Cell>> _reachableCells;

  /// list of cells occupied by an enemy unit
  std::vector<std::shared_ptr<Cell>> _enemyPositions;
};



/**
 * \enum e_path_shape
 * \brief Help matching which element we want to display, drawing the path
 * \note Values match needed sprite rotation angle.
 */
enum class e_path_shape
{
  // Arrows (last of the path)
  LAST_UP = 0,
  LAST_DOWN = 180,
  LAST_LEFT = 90,
  LAST_RIGHT = 270,

  // Rectangles
  UP = 360,
  DOWN = 540, // same as UP
  LEFT = 630,
  RIGHT = 450, // same as LEFT

  // Corners (clockwise direction)
  CORNER_RIGHT_UP = 720,
  CORNER_UP_LEFT = 990,
  CORNER_LEFT_DOWN = 900,
  CORNER_DOWN_RIGHT = 810,

  // Same as above, just to help building the path
  CORNER_UP_RIGHT = 1080,
  CORNER_LEFT_UP = 1350,
  CORNER_DOWN_LEFT = 1260,
  CORNER_RIGHT_DOWN = 1170,

  NONE
};



/**
 * \enum e_direction
 * \brief Stores directions + rotation angles. Used for paths
 */
enum class e_direction
{
  NONE = 0,

  // these values matches rotation angle
  // (sprites are always oriented to the top
  //   rotation are done in clockwise direction)
  UP = 360,
  DOWN = 540,
  LEFT = 630,
  RIGHT = 450
};



#endif /* !PATH_FINDING_HH_ */
