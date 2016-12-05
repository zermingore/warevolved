/**
 * \file
 * \author Zermingore
 * \brief Map class definition.
 */

#ifndef MAP_HH_
# define MAP_HH_

# include <common/include.hh>
# include <common/using.hh>

class Cell;
class Battle;
class Unit;

enum class e_terrain;
enum class e_unit;


/**
 * \class Map
 * \brief Represents the game map.
 */
class Map
{
public:
  /// \typedef player's units as a list
  using unit_list = std::map<size_t, std::list<std::shared_ptr<Unit>>>;

  /**
   * \class MapGraphicsProperties
   * \brief Graphics properties of the Map (cell sizes, grid thickness, ...)
   */
  class MapGraphicsProperties
  {
  public:
    /**
     * \brief Constructor
     *
     * Initialize attributes with default values.
     */
    MapGraphicsProperties();

    /**
     * \brief cell width getter.
     * \return cell width in pixels.
     */
    size_t cellWidth() const { return _cellWidth; }

    /**
     * \brief cell height getter.
     * \return cell height in pixels.
     */
    size_t cellHeight() const { return _cellHeight; }

    /**
     * \brief grid thickness getter.
     * \return grid thickness in pixels.
     */
    size_t gridThickness() const { return _gridThickness; }

    /**
     * \brief offset of the grid (from the left border of the window) getter.
     * \return grid offset, in x.
     */
    size_t gridOffsetX() const { return _gridOffsetX; }

    /**
     * \brief offset of the grid (from the top border of the window) getter.
     * \return grid offset, in y.
     */
    size_t gridOffsetY() const { return _gridOffsetY; }

    /**
     * \brief cell width setter.
     * \param width cell width in pixels.
     */
    void setCellWidth(size_t width) { _cellWidth = width; }

    /**
     * \brief cell height setter.
     * \param height cell height in pixels.
     */
    void setCellHeight(size_t height) { _cellHeight = height; }

    /**
     * \brief grid thickness setter.
     * \param thickness of the grid in pixels.
     */
    void setGridThickness(size_t thickness) { _gridThickness = thickness; }

    /**
     * \brief offset of the grid (from the left border of the window) setter.
     * \param x offset.
     */
    void setGridOffsetX(size_t grid_offset_x) { _gridOffsetX = grid_offset_x; }

    /**
     * \brief offset of the grid (from the top border of the window) setter.
     * \param y offset.
     */
    void setGridOffsetY(size_t grid_offset_y) { _gridOffsetY = grid_offset_y; }


  private:
     size_t _cellWidth;     ///< cells width in pixels
     size_t _cellHeight;    ///< cells height in pixels
     size_t _gridThickness; ///< thickness of the grid
     size_t _gridOffsetX;   ///< X grid offset (from the window left border)
     size_t _gridOffsetY;   ///< Y grid offset (from the window top border)
  };


  /// remove default constructor as we need the dimensions of the map
  Map() = delete;

  /**
   * \brief Constructs a map of nbColumns x nbLines
   *
   * Initializes the map as follow:
   *   Puts units where needed;
   *   Sets right Terrains;
   *   Asks ResourcesManager to loads needed Resources
   *
   * \param battle pointer on the battle in which this map is
   * \param nbColumns Number of columns required
   * \param nbLines Number of lines required
   */
  Map(Battle* battle, const size_t nb_lines, const size_t nb_columns);

  /**
   * \brief _nbColumns getter
   *
   * \return number of columns
   */
  size_t nbColumns() const { return _nbColumns; }

  /**
   * \brief _nbLines getter
   * \return number of lines
   */
  size_t nbLines() const { return _nbLines; }

  /**
   * \brief Graphics properties getter
   * \return a pointer on the graphics properties class
   */
  std::shared_ptr<MapGraphicsProperties> graphicsProperties() const {
    return _graphicsProperties;
  }


  /**
   * \brief gets the unit at coordinates (x, y)
   *
   * \param x Coordinates according to columns
   * \param y Coordinates according to lines
   *
   * \return the enum index in e_unit matching the unit
   *   located at coordinates (x, y)
   */
  std::shared_ptr<Unit> unit(const size_t line, const size_t column) const;

  /**
   * \brief gets the unit at c's coordinates.
   * \param c targeted Cell's coordinates.
   * \return the enum index in e_unit matching the unit
   *   located at coordinates (c.x, c.y).
   */
  std::shared_ptr<Unit> unit(const Coords& c) const;

  /**
   * \brief Marks the Unit located at the given coordinates as selected.
   * \param c coordinates where the Unit to select is located
   * \return a pointer to the updated selected unit on success
   *   returns nullptr and sets the selected unit to nullptr otherwise
   *   (this happens if no unit was found at the given coordinates)
   */
  std::shared_ptr<Unit> selectUnit(const Coords c);

  /**
   * \brief gets the terrain at coordinates (x, y).
   *
   * \param x Coordinates according to columns.
   * \param y Coordinates according to lines.
   *
   * \return the enum index in e_terrain matching the terrain
   *   located at coordinates (x, y).
   */
  e_terrain getTerrain(const size_t line, const size_t column) const;

  /**
   * \brief _cells array getter.
   * \return The cells array.
   */
  auto cells() const { return _cells; }

  /**
   * \brief builds a new unit of type \param unit
   *
   * \param type type of the new unit
   * \param line line to set the new unit
   * \param column column to set the new unit
   */
  void newUnit(const e_unit type, const size_t line, const size_t column);

  /**
   * \brief moves the selected unit to the current cursor location
   */
  void moveUnit();

  /**
   * \brief moves given unit to the given coordinates
   */
  void moveUnit(std::shared_ptr<Unit> u, const Coords c);

  /**
   * \brief reset all units played boolean to false
   */
  void endTurn();

  /**
   * \brief operator to allow getting a cell calling map[i][j]
   * returns a vector of pointers to Cell
   * To get the requested cell, use the second coordinate as vector index
   *
   * \param line requested Cell coordinate
   *
   * \return a vector of pointers to Cell
   */
  auto operator[] (const size_t line) { return _cells[line]; }

  /**
   * \brief ascii art dump of the map
   */
  void dump();



private:
  std::shared_ptr<Battle> _battle; ///< Battle in which this map belong to

  size_t _nbColumns; ///< number of columns (x coordinate)
  size_t _nbLines;   ///< number of lines (y coordinate)

  /// 2D Array of every cells of the map
  std::vector<std::vector<std::shared_ptr<Cell>>> _cells;

  /// map of units: <player, unit_list>
  unit_list _units;

  /// list of map graphics properties (cells size, grid thickness, ...)
  std::shared_ptr<Map::MapGraphicsProperties> _graphicsProperties;

  /// Current selected unit
  std::shared_ptr<Unit> _selectedUnit;
};


#endif /* !MAP_HH_ */
