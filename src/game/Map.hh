#ifndef MAP_HH_
# define MAP_HH_

# include <memory>

# include <game/units/Unit.hh>
# include <common/enums/terrains.hh>
# include <common/enums/units.hh>

class MapGraphicsProperties;
class Battle;
class Cursor;


/** \class represents the game map
 */
class Map
{
  typedef std::shared_ptr<std::map<size_t, std::list<std::shared_ptr<Unit>>>> unit_list;


public:
  /** \brief removing default constructor
   */
  Map() = delete;

  /** \brief Constructs a map of nbColumns x nbLines
   ** \param nbColumns Number of columns required
   ** \param nbLines Number of lines required
   ** calls this->init() to initialize a fresh Map
   */
  Map(size_t nbColumns, size_t nbLines// , std::shared_ptr<Battle> battle
    );

  void setBattle(Battle* battle);

  /** \brief Initializes the map
   **   Puts units where needed;
   **   Sets right Terrains;
   **   Asks ResourcesManager to loads needed Resources
   */
  void init();

  /** \brief _nbColumns getter
   ** \return number of columns
   */
  inline size_t nbColumns() const { return _nbColumns; }

  /** \brief _nbLines getter
   ** \return number of lines
   */
  inline size_t nbLines() const { return _nbLines; }

  /** \brief Graphics properties getter
   ** \return a pointer on the graphics properties class
   */
  inline std::shared_ptr<MapGraphicsProperties> graphicsProperties() const
  { return _graphicsProperties; }

  /** \brief gets the unit at coordinates (x, y)
   **
   ** \param x Coordinates according to columns
   ** \param y Coordinates according to lines
   **
   ** \return the enum index in e_unit matching the unit
   **   located at coordinates (x, y)
   */
  std::shared_ptr<Unit> unit(size_t x, size_t y) const;

  /** \brief gets the unit at c's coordinates
   **
   ** \param c targeted Cell's coordinates
   **
   ** \return the enum index in e_unit matching the unit
   **   located at coordinates (c.x, c.y)
   */
  std::shared_ptr<Unit> unit(Coords c) const;

  /** \brief gets the terrain at coordinates (x, y)
   **
   ** \param x Coordinates according to columns
   ** \param y Coordinates according to lines
   **
   ** \return the enum index in e_terrain matching the terrain
   **   located at coordinates (x, y)
   */
  terrain getTerrain(size_t x, size_t y) const;

  /** \brief _cells array getter
   ** \return a reference over the cells array
   */
  inline std::vector<std::vector<std::shared_ptr<Cell>>> cells() const
  { return _cells; }

  /** \brief returns the Cell which coordinates are x and y
   ** \param x requested Cell x coordinate
   ** \param y requested Cell y coordinate
   ** \return a pointer over the requested Cell
   */
  inline std::shared_ptr<Cell> cell(size_t x, size_t y) const
  { return _cells[x][y]; }

  /** \brief builds a new unit of type \param unit
   ** \param unit type of the new unit
   */
  void newUnit(enum unit unit, size_t line, size_t column);

  /** \brief sets the given unit in the cells array
   ** \param unit to set
   */
  // void setUnit(std::shared_ptr<Unit> u);

  /** \brief moves the selected unit to the current cursor location
   */
  void moveUnit();

  /** \brief moves given unit to the given coordinates
   */
  void moveUnit(std::shared_ptr<Unit> u, Coords c);

  /** \brief returns all units
   */
  unit_list units() const
  { return _units; }

  /** \brief returns the cursor of the given player
   */
  std::shared_ptr<Cursor> cursor(size_t player);

  /** \brief reset all units played boolean to false
   */
  void endTurn();

  /** \brief sets current player cursor coordinates to the given coordinates
   */
  void setCursorCoords(Coords coords);


  /** \brief returns battle current player
   */
  size_t currentPlayer();


private:
  size_t _nbColumns; ///< number of columns (x coordinate)
  size_t _nbLines; ///< number of lines (y coordinate)
  std::shared_ptr<Battle> _battle; ///< Battle in which this map belong to

  ///< 2D Array of every cells of the map
  std::vector<std::vector<std::shared_ptr<Cell>>> _cells;

  ///< map of units: <player, unit_list>
  std::shared_ptr<std::map<size_t, std::list<std::shared_ptr<Unit>>>> _units;

  ///< map of players cursors (map[player_id] = cursor)
  std::map<size_t, std::shared_ptr<Cursor>> _cursors;

  ///< list of map graphics properties (cells size, grid thickness, ...)
  std::shared_ptr<MapGraphicsProperties> _graphicsProperties;
};

#endif /* !MAP_HH_ */
