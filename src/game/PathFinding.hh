/**
 * \file
 * \date July 18, 2013
 * \author Zermingore
 */

#ifndef PATH_FINDING_HH_
# define PATH_FINDING_HH_

# include <vector>
# include <memory>
# include <structures/Vector.hh>
# include <graphics/Sprite.hh>

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
   * \brief Deleted default constructor: The origin is required
   */
  PathFinding() = delete;

  /**
   * \brief Instantiate a PathFinding based on the given origin unit
   * \param origin Unit origin of the path
   */
  PathFinding(std::shared_ptr<Unit> origin);

  /**
   * \brief Destructor: clears the graphics attributes
   */
  ~PathFinding();


  /**
   * \brief List of enemy positions getter
   * \return a pointer on the vector of enemy positions
   */
  auto getEnemyPositions() { return _enemyPositions; }

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
   */
  void drawPath();

  /**
   * \brief clears current path
   * calls deleteImagesVector, freeing images
   */
  void clearPath();

  /**
   * \brief hides crossable cells
   */
  void hideAllowedPath();

  /**
   * \brief Sets cells highlight as follow:
   * - Highlight reachable cells (at moving range)
   * - Highlight enemy units at shooting range
   * - Highlight friendly units at moving range
   */
  void highlightCells();

  /**
   * \brief Return the list of available targets
   * \param ref Unit for which and from where the targets will be seek
   * \param coords Coordinates where the attacker is located
   */
  std::shared_ptr<std::vector<std::shared_ptr<Cell>>>
  getTargets(std::shared_ptr<Unit> ref, Coords coords);



private:
  /**
   * \brief returns the sprite matching e_path_shape
   * does the rotation if needed
   * \return the image matching e_path_shape
   */
  std::shared_ptr<graphics::Sprite> getSprite(size_t index);


  /**
   * \brief updates current cell coordinates
   *   according to \param direction
   * \param direction current move direction
   */
  void updateCurrentCell(e_direction direction);

  /**
   * \brief returns shape matching _direction (index parameter)
   * \param index index in _direction vector.
   * \return shape of _direction[\param index]
   *   according to the next direction (for smooth corners).
   */
  e_path_shape getShape(size_t index);


  /**
   * \brief returns the Manhattan distance between two cells
   * \param a first cell
   * \param b second cell
   * \return the distance between the two cells
   */
  size_t manhattan(Coords a, Coords b);



  std::shared_ptr<Unit> _origin;  ///< Unit at the origin of the path
  Coords _current;                ///< Current cell coordinates.
  Coords _lastPosition;           ///< Last position of the path

  size_t _maxLength;     ///< Path max length.
  size_t _currentLength; ///< Path current length.

  std::shared_ptr<Map> _map; ///< Do not access Battle all the time

  ///< List of path directions filled through addNextDirection.
  std::vector<e_direction> _directions;

  ///< list of reachable cells for the selected unit
  std::vector<std::shared_ptr<Cell>> _reachableCells;

  ///< list of cells occupied by an enemy unit
  std::vector<std::shared_ptr<Cell>> _enemyPositions;
};


#endif /* !PATH_FINDING_HH_ */
