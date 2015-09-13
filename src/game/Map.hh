#ifndef MAP_HH_
# define MAP_HH_

# include <common/include.hh>
# include <common/enums/terrains.hh>
# include <common/enums/units.hh>

class Cell;
class Battle;
class Cursor;
class Unit;


/** \class represents the game map
 */
class Map
{
public:
  ///< \typedef player's units as a list
  typedef std::map<size_t, std::list<std::shared_ptr<Unit>>> unit_list;

  /** \class graphics properties
   */
  class MapGraphicsProperties
  {
  public:
    MapGraphicsProperties();

    inline unsigned int cellWidth() { return _cellWidth; }
    inline unsigned int cellHeight() { return _cellHeight; }
    inline unsigned int gridThickness() { return _gridThickness; }
    inline unsigned int gridOffsetX() { return _gridOffsetX; }
    inline unsigned int gridOffsetY() { return _gridOffsetY; }


    inline void setCellWidth(unsigned int cell_width) { _cellWidth = cell_width; }
    inline void setCellHeight(unsigned int cell_height) { _cellHeight = cell_height; }
    inline void setGridThickness(unsigned int grid_thickness) { _gridThickness = grid_thickness; }
    inline void setGridOffsetX(unsigned int grid_offset_x) { _gridOffsetX = grid_offset_x; }
    inline void setGridOffsetY(unsigned int grid_offset_y) { _gridOffsetY = grid_offset_y; }


  private:
     size_t _cellWidth; ///< cells width
     size_t _cellHeight; ///< cells height
     size_t _gridThickness; ///< thickness of the grid
     size_t _gridOffsetX; ///< X offset of the grid (related to the window)
     size_t _gridOffsetY; ///< Y offset of the grid (related to the window)
  };


  /** \brief removing default constructor
   */
  Map() = delete;

  /** \brief Constructs a map of nbColumns x nbLines
   ** \param battle pointer on the battle in which this map is
   ** \param nbColumns Number of columns required
   ** \param nbLines Number of lines required
   ** calls this->init() to initialize a fresh Map
   */
  Map(Battle* battle, size_t nbColumns, size_t nbLines);

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
  inline std::shared_ptr<MapGraphicsProperties> graphicsProperties()
  { return _graphicsProperties; }

  /** \brief returns the current player in the map
   ** \return current player's identifier
   */
  size_t currentPlayer() const;

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

  /** \brief returns the cursor of the given player
   */
  std::shared_ptr<Cursor> cursor(size_t player);

  /** \brief reset all units played boolean to false
   */
  void endTurn();

  /** \brief sets current player cursor coordinates to the given coordinates
   */
  void setCursorCoords(Coords coords);


private:
  size_t _nbColumns; ///< number of columns (x coordinate)
  size_t _nbLines; ///< number of lines (y coordinate)
  std::shared_ptr<Battle> _battle; ///< Battle in which this map belong to

  ///< 2D Array of every cells of the map
  std::vector<std::vector<std::shared_ptr<Cell>>> _cells;

  ///< map of units: <player, unit_list>
  unit_list _units;

  ///< map of players cursors (map[player_id] = cursor)
  std::map<size_t, std::shared_ptr<Cursor>> _cursors;

  ///< list of map graphics properties (cells size, grid thickness, ...)
  std::shared_ptr<Map::MapGraphicsProperties> _graphicsProperties;
};

#endif /* !MAP_HH_ */
