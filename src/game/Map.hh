/**
 * \file
 * \date April 19, 2013
 * \author Zermingore
 * \brief Map class definition and enum e_attack_result definition
 */

#ifndef GAME_MAP_HH_
# define GAME_MAP_HH_

# include <mutex>
# include <memory>
# include <optional>
# include <vector>
# include <list>
# include <map>
# include <cstddef>

# include <lib/pugixml.hh>

# include <common/using.hh>

# include <game/Building.hh>

class Cell;
class Unit;
class Building;

enum class e_attack_result; // definition follows
enum class e_terrain;
enum class e_unit;


/**
 * \class Map
 * \brief Represents the game map.
 */
class Map
{
  class MapIterator;

public:
  /**
   * \typedef unit_list
   * \brief list of units, per player
   */
  using unit_list = std::map<size_t, std::list<std::shared_ptr<Unit>>>;


  /// remove default constructor as we need the dimensions of the map
  Map() = delete;

  /**
   * \brief Constructs a map of nb_columns x nb_lines
   *
   * Initializes the map as follow:
   *   Puts units where needed;
   *   Sets right Terrains;
   *   Asks ResourcesManager to loads needed Resources
   *
   * \param nb_columns Number of columns required
   * \param nb_lines Number of lines required
   */
  Map(size_t nb_columns, size_t nb_lines);


  /**
   * \brief Get the building containing the given coordinates
   * \param coord Coordinates in the building
   */
  std::optional<Building> getBuilding(const Coords coord);

  /**
   * \brief Add a building to the Map
   * \param coords List of Cell's coordinates where the building is located
   */
  void addBuilding(const std::vector<std::shared_ptr<Coords>> &coords);

  /**
   * \brief _nbColumns getter
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
   * \param column Coordinates according to columns
   * \param line Coordinates according to lines
   *
   * \return the enum index in e_unit matching the unit
   *   located at coordinates (x, y)
   */
  std::shared_ptr<Unit> unit(size_t column, size_t line) const;

  /**
   * \brief gets the unit at c's coordinates.
   * \param c targeted Cell's coordinates.
   * \return the enum index in e_unit matching the unit
   *   located at coordinates (c.c, c.l).
   */
  std::shared_ptr<Unit> unit(const Coords& c) const;

  /**
   * \brief Marks the Unit located at the given coordinates as selected.
   * \param c coordinates where the Unit to select is located
   * \note A unit must be located at given coordinates
   */
  void selectUnit(const Coords& c);

  /**
   * \brief selected unit getter
   * \return a pointer on the currently selected unit, if any
   * \note Find a Unit under current Player's cursor if _selectedUnit is NULL
   */
  std::shared_ptr<Unit> selectedUnit();

  /**
   * \brief sets the terrain at given coordinates
   * \param column Coordinates according to columns.
   * \param line Coordinates according to lines.
   * \param terrain Terrain to assign for the designated Cell
   */
  void setTerrain(size_t column, size_t line, e_terrain terrain);

  /**
   * \brief Clear, for each cell the highlight flag
   */
  void clearHighlights();

  /**
   * \brief get the cell at given coordinates
   * \param coords the coordinates of the Cell to retrieve
   * \return The cell at coords coordinates
   */
  auto cell(Coords coords) const { return _cells[coords.c][coords.l]; }

  /**
   * \brief _cells array getter.
   * \return The cells array.
   */
  auto cells() const { return _cells; }

  /**
   * \brief builds and keep a new Unit
   * \param type type of the new unit
   * \param column column where to set the new unit
   * \param line line where to set the new unit
   * \param player_id player to which the unit belongs to
   * \param hp Health Points of the newly created Unit
   * \param played Set the Unit as played for this turn
   * \note Throws if the column/line arguments are greater than the Map size
   */
  void newUnit(e_unit type,
               size_t column,
               size_t line,
               size_t player_id,
               int hp,
               bool played);

  /**
   * \brief Keep a pointer on a Unit
   * \param unit Unit to keep track of
   * \param line line where to set the new unit
   * \param column column where to set the new unit
   * \note Throws if the column/line arguments are greater than the Map size
   */
  void newUnit(const std::shared_ptr<Unit>& unit, size_t column, size_t line);

  /**
   * \brief moves the _selectedUnit to the given coordinates
   * \param c Destination coordinates
   */
  void moveUnit(const Coords& c);

  /**
   * \brief reset all units played boolean to false
   */
  void endTurn();


  /**
   * \brief computes and return the result of the fight
   * \param attacker_status attacker status after the fight
   * \param defender_status defender status after the fight
   * \return the attack result
   */
  e_attack_result attackResult(bool attacker_status,
                               bool defender_status) const;

  /**
   * \brief Perform the attack of the _selectedUnit over the defender
   * \param defender Unit defending the attack
   * \return the result of the attack (which unit died, if any)
   */
  e_attack_result attack(const std::shared_ptr<Unit>& defender);

  /**
   * \brief Perform the attack of the _selectedUnit on the target_cell
   * \param target_cell target of the attack (may contain an unit)
   * \return the result of the attack (which unit died, if any)
   */
  e_attack_result attack(const std::shared_ptr<Cell>& target_cell);

  /**
   * \brief Attack the building including the given coordinates
   * \param attackerCoords Attacker coordinates; belongs to the building
   * \return The result of the attack (NONE_DIED on empty building)
   * \note The two opponents will fight until one has no HPs left
   * \note The defender attacks first; There is no strike back concept
   * \note Defender's cover is greater than the attacker's one
   */
  e_attack_result attackBuilding(const Coords attackerCoords);

  /**
   * \brief Removes a Unit from the map. This is useful to group units
   * \param unit Unit to hide
   * \warning The unit will no longer be accessible from the map / cells
   * \warning The unit will be deleted from the map => keep a pointer on it
   */
  void stashUnit(const Unit& unit);

  /**
   * \brief builds and keep a new Unit; Useful to break a crew
   * \param unit Unit to add to the Map
   */
  void stashPopUnit(const Unit& unit);


  /**
   * \brief operator to allow getting a cell calling map[i][j]
   * returns a vector of pointers to Cell
   * To get the requested cell, use the second coordinate as vector index
   *
   * \param column requested Cell column coordinate
   * \return a vector of pointers to Cell
   */
  auto operator[] (size_t column) { return _cells[column]; }

  /**
   * \brief Dump the map, in a XML document
   * \return the dumped map, in a new XML document
   */
  std::unique_ptr<pugi::xml_document> dump();


  /**
   * \brief MapIterator first value
   * \return A MapIterator on the first Cell
   */
  MapIterator begin() { return MapIterator(*this, 0, 0); }

  /**
   * \brief MapIterator last value
   * \return A MapIterator on the first out of bound Cell
   * \note The {0, _nbLines} coordinates is out of Map bounds
   */
  MapIterator end() { return MapIterator(*this, 0, _nbLines); }


private:
  /**
   * \brief Helper function to compute the damages values
   * \param attacker Attacking unit
   * \param defender Unit under attack
   * \return A couple: (attacker damages, defender damages)
   * \note The defender damages is 0 if the attack is lethal
   * \note The damages are in [| 1; +inf |]
   */
  std::pair<size_t, size_t> damageValues(const Unit& attacker,
                                         const Unit& defender);

  /**
   * \brief Valid coordinates sanity checks
   * \param column must be <= _nbColumns
   * \param line must be <= _nbLines
   * \note Throws if the preconditions are not respected
   */
  constexpr void boundaryChecks(const size_t column, const size_t line);


  size_t _nbColumns; ///< number of columns (x coordinate)
  size_t _nbLines;   ///< number of lines (y coordinate)

  /// 2D Array of every cells of the map
  std::vector<std::vector<std::shared_ptr<Cell>>> _cells;

  /// map of units: <player, unit_list>
  unit_list _units;

  /// Current selected unit
  std::shared_ptr<Unit> _selectedUnit;

  /// Locking while updating the selected unit
  std::mutex _lockSelectedUnitUpdate;

  /// List of buildings
  std::vector<Building> _buildings;


  /**
   * \class MapIterator
   * \brief Custom iterator on the Map cells
   * \note Map private class
   */
  class MapIterator
  {
    public:
      using iterator_category = std::output_iterator_tag;
      using value_type = Cell;
      using difference_type = void;
      using pointer = Cell*;
      using reference = Cell&;

      /**
       * \brief Constructor
       * \param map Map in order to get the cells list and Map dimensions
       * \param col_idx Pointed Cell column index
       * \param line_idx Pointed Cell line index
       */
      explicit MapIterator(Map& map, size_t col_idx = 0, size_t line_idx = 0)
        : _cells(map.cells())
        , _colIdx(col_idx)
        , _lineIdx(line_idx)
        , _nbColumns(map.nbColumns())
        , _nbLines(map.nbLines())
      {
      }

      /**
       * \brief Increment operator (postfix)
       */
      MapIterator& operator++();

      /**
       * \brief Increment operator (prefix)
       */
      Cell operator++(int);

      /**
       * \brief Comparison operator
       * \param rhs Right hand side operand
       * \return wether if the Cell coordinates of both operator are the same
       */
      bool operator!=(const MapIterator& rhs) const {
        return _colIdx != rhs._colIdx || _lineIdx != rhs._lineIdx;
      }

      /**
       * \brief Derefence operator
       * \return the Cell pointed by the operator coordinates
       */
      std::shared_ptr<Cell> operator*() { return _cells[_colIdx][_lineIdx]; }


    private:
      std::vector<std::vector<std::shared_ptr<Cell>>> _cells; ///< Map cells
      size_t _colIdx;    ///< Cell column index
      size_t _lineIdx;   ///< Cell line index
      size_t _nbColumns; ///< Map nb columns
      size_t _nbLines;   ///< Map nb lines
  };
};



/**
 * \enum e_attack_result
 * \brief Identifies the result of an attack
 */
enum class e_attack_result
{
  INVALID = 0,
  NONE_DIED,
  ATTACKER_DIED,
  DEFENDER_DIED,
  BOTH_DIED,
};

#endif /* !GAME_MAP_HH_ */
