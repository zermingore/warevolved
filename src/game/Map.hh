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
  /// \typedef player's units as a list
  typedef std::map<size_t, std::list<std::shared_ptr<Unit>>> unit_list;

  /** \class MapGraphicsProperties
   * \brief Graphics properties of the Map
   */
  class MapGraphicsProperties
  {
  public:
    MapGraphicsProperties();

    unsigned int cellWidth() { return _cellWidth; }
    unsigned int cellHeight() { return _cellHeight; }
    unsigned int gridThickness() { return _gridThickness; }
    unsigned int gridOffsetX() { return _gridOffsetX; }
    unsigned int gridOffsetY() { return _gridOffsetY; }


    void setCellWidth(unsigned int cell_width) { _cellWidth = cell_width; }
    void setCellHeight(unsigned int cell_height) { _cellHeight = cell_height; }
    void setGridThickness(unsigned int grid_thickness) { _gridThickness = grid_thickness; }
    void setGridOffsetX(unsigned int grid_offset_x) { _gridOffsetX = grid_offset_x; }
    void setGridOffsetY(unsigned int grid_offset_y) { _gridOffsetY = grid_offset_y; }


  private:
     size_t _cellWidth;     ///< cells width
     size_t _cellHeight;    ///< cells height
     size_t _gridThickness; ///< thickness of the grid
     size_t _gridOffsetX;   ///< X offset of the grid (related to the window)
     size_t _gridOffsetY;   ///< Y offset of the grid (related to the window)
  };


  /// \brief remove default constructor as we need the dimensions of the map
  Map() = delete;

  /** \brief Constructs a map of nbColumns x nbLines
   **
   ** Initializes the map as follow:
   **   Puts units where needed;
   **   Sets right Terrains;
   **   Asks ResourcesManager to loads needed Resources
   **
   ** \param battle pointer on the battle in which this map is
   ** \param nbColumns Number of columns required
   ** \param nbLines Number of lines required
   */
  Map(Battle* battle, size_t nb_columns, size_t nb_lines);

  /// initializes the cursors
  void initCursors();

  /** \brief _nbColumns getter
   ** \return number of columns
   */
  size_t nbColumns() const { return _nbColumns; }

  /** \brief _nbLines getter
   ** \return number of lines
   */
  size_t nbLines() const { return _nbLines; }

  /** \brief Graphics properties getter
   ** \return a pointer on the graphics properties class
   */
  std::shared_ptr<MapGraphicsProperties> graphicsProperties()
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
  e_terrain getTerrain(size_t x, size_t y) const;

  /** \brief _cells array getter
   ** \return a reference over the cells array
   */
  std::vector<std::vector<std::shared_ptr<Cell>>> cells() const
  { return _cells; }

  /** \brief builds a new unit of type \param unit
   ** \param unit type of the new unit
   */
  void newUnit(e_unit u, size_t line, size_t column);

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

  /** \brief operator to allow getting a cell calling map[i][j]
   * returns the Cell which coordinates are x and y
   *
   * \param x requested Cell x coordinate
   * \param y requested Cell y coordinate
   *
   * \return a pointer to the requested Cell
   */
  std::vector<std::shared_ptr<Cell>> operator[] (size_t line) { return _cells[line]; }


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
