#ifndef MAP_HH_
# define MAP_HH_

# include <common/include.hh>
# include <common/enums/units.hh>
# include <common/enums/terrains.hh>
# include <game/Cell.hh>
# include <game/units/Unit.hh>
# include <resources/ResourcesManager.hh>


/** \brief class which represents the game map
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
  { return _cells[x][y].unit(); }

  /** \brief gets the unit at v's coordinates
   **
   ** \param v targeted cell's coordinates
   **
   ** \return the enum index in e_unit matching the unit
   **   located at coordinates (v.x, v.y)
   */
  std::shared_ptr<Unit> unit(Coords v) { return _cells[v.x][v.y].unit(); }

  /** \brief gets the terrain at coordinates (x, y)
   **
   ** \param x Coordinates according to columns
   ** \param y Coordinates according to lines
   **
   ** \return the enum index in e_terrain matching the terrain
   **   located at coordinates (x, y)
   */
  e_terrain getTerrain(unsigned int x, unsigned int y)
  { return _cells[x][y].getTerrain(); }

  /** \brief gets the terrain image at coordinates (x, y)
   **
   ** \param x Coordinates according to columns
   ** \param y Coordinates according to lines
   **
   ** \return the Image matching the terrain
   **   located at coordinates (x, y)
   */
  // Image *getTerrainImage(unsigned int x, unsigned int y);

  /** \brief _cells array getter
   ** \return a reference over the cells array
   */
  inline std::vector<std::vector<Cell>> &cells() { return _cells; }

  /** \brief returns the Cell which coordinates are x and y
   ** \param x requested Cell x coordinate
   ** \param y requested Cell y coordinate
   ** \return a reference over the requested Cell
   */
  inline Cell &cell(unsigned int x, unsigned int y)
  { return _cells[x][y]; }

  /** \brief sets the given unit in the cells array
   ** \param unit to set
   */
  void setUnit(std::shared_ptr<Unit> u)
  { _cells[u->cellX()][u->cellY()].setUnit(u); }

  /** \brief moves the selected unit to the current cursor location
   */
  void moveUnit();


private:
  unsigned int _nbColumns; ///< number of columns (x coordinate)
  unsigned int _nbLines; ///< number of lines (y coordinate)
  std::vector<std::vector<Cell>> _cells; ///< 2D Array of every cells of the map
};

#endif /* !MAP_HH_ */
