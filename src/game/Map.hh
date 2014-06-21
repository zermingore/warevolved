#ifndef MAP_HH_
# define MAP_HH_

# include <common/include.hh>
# include <common/enums/units.hh>
# include <common/enums/terrains.hh>
# include <game/Cell.hh>
# include <game/units/Unit.hh>
# include <resources/ResourcesManager.hh>
# include <game/Player.hh>


/** \class represents the game map
 */
class Map
{
public:
  /** \brief Constructs a map of nbColumns x nbLines
   ** \param nbColumns Number of columns required
   ** \param nbLines Number of lines required
   ** calls this->init() to initialize a fresh Map
   */
  Map(unsigned int nbColumns, unsigned int nbLines);

  /** \brief Initializes the map
   **   Puts units where needed;
   **   Sets right Terrains;
   **   Asks ResourcesManager to loads needed Resources
   */
  void init();

  /** \brief _nbColumns getter
   ** \return number of columns
   */
  inline unsigned int nbColumns() const { return _nbColumns; }

  /** \brief _nbLines getter
   ** \return number of lines
   */
  inline unsigned int nbLines() const { return _nbLines; }

  /** \brief gets the unit at coordinates (x, y)
   **
   ** \param x Coordinates according to columns
   ** \param y Coordinates according to lines
   **
   ** \return the enum index in e_unit matching the unit
   **   located at coordinates (x, y)
   */
  std::shared_ptr<Unit> unit(unsigned int x, unsigned int y)
  { return _cells[x][y]->unit(); }

  /** \brief gets the unit at c's coordinates
   **
   ** \param c targeted Cell's coordinates
   **
   ** \return the enum index in e_unit matching the unit
   **   located at coordinates (c.x, c.y)
   */
  std::shared_ptr<Unit> unit(Coords c) { return _cells[c.x][c.y]->unit(); }

  /** \brief gets the terrain at coordinates (x, y)
   **
   ** \param x Coordinates according to columns
   ** \param y Coordinates according to lines
   **
   ** \return the enum index in e_terrain matching the terrain
   **   located at coordinates (x, y)
   */
  e_terrain getTerrain(unsigned int x, unsigned int y)
  { return _cells[x][y]->getTerrain(); }

  /** \brief _cells array getter
   ** \return a reference over the cells array
   */
  inline std::vector<std::vector<std::shared_ptr<Cell>>> cells() { return _cells; }

  /** \brief returns the Cell which coordinates are x and y
   ** \param x requested Cell x coordinate
   ** \param y requested Cell y coordinate
   ** \return a pointer over the requested Cell
   */
  inline std::shared_ptr<Cell> cell(unsigned int x, unsigned int y)
  { return _cells[x][y]; }

  /** \brief sets the given unit in the cells array
   ** \param unit to set
   */
  void setUnit(std::shared_ptr<Unit> u)
  { _cells[u->cellX()][u->cellY()]->setUnit(u); }

  /** \brief moves the selected unit to the current cursor location
   */
  void moveUnit();


private:
  unsigned int _nbColumns; ///< number of columns (x coordinate)
  unsigned int _nbLines; ///< number of lines (y coordinate)

  ///< 2D Array of every cells of the map
  std::vector<std::vector<std::shared_ptr<Cell>>> _cells;

  ///< players in this battle
  std::shared_ptr<std::vector<std::shared_ptr<Player>>> _players;

};

#endif /* !MAP_HH_ */
