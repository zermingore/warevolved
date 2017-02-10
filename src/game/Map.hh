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
   * \param nbColumns Number of columns required
   * \param nbLines Number of lines required
   */
  Map(const size_t nb_columns, const size_t nb_lines);

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
   * \note A unit must be located at given coordinates
   */
  void selectUnit(const Coords c);

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
   * \param player_id player to which the unit belongs to
   *
   * \note player_id defaults to -1
   *   In this case, the unit is assigned to the current player
   */
  void newUnit(const e_unit type,
               const size_t column,
               const size_t line,
               int player_id = -1);

  /**
   * \brief moves the _selectedUnit to the given coordinates
   * \param c Destination coordinates
   */
  void moveUnit(const Coords c);

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
  auto operator[] (const size_t column) { return _cells[column]; }

  /**
   * \brief ascii art dump of the map
   */
  void dump();



private:
  size_t _nbColumns; ///< number of columns (x coordinate)
  size_t _nbLines;   ///< number of lines (y coordinate)

  /// 2D Array of every cells of the map
  std::vector<std::vector<std::shared_ptr<Cell>>> _cells;

  /// map of units: <player, unit_list>
  unit_list _units;

  /// Current selected unit
  std::shared_ptr<Unit> _selectedUnit;
};


#endif /* !MAP_HH_ */
