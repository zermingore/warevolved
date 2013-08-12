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

  /** \brief Destructor
   */
  ~Map();

  /** \brief Initializes the map
   **   Puts units where needed;
   **   Sets right Terrains;
   **   Asks ResourcesManager to loads needed Resources
   */
  void init();

  /** \brief getter for _nbColumns
   */
  unsigned int getNbColumns();

  /** \brief getter for _nbLines
   */
  unsigned int getNbLines();

  /** \brief gets the unit at coordinates (x, y)
   **
   ** \param x Coordinates according to columns
   ** \param y Coordinates according to lines
   **
   ** \return the enum index in e_unit matching the unit
   **   located at coordinates (x, y)
   */
  Unit *getUnit(unsigned int x, unsigned int y);

  /** \brief gets the unit at v's coordinates
   **
   ** \param v targeted cell's coordinates
   **
   ** \return the enum index in e_unit matching the unit
   **   located at coordinates (v.x, v.y)
   */
  Unit *getUnit(Coords v);

  /** \brief gets the terrain at coordinates (x, y)
   **
   ** \param x Coordinates according to columns
   ** \param y Coordinates according to lines
   **
   ** \return the enum index in e_terrain matching the terrain
   **   located at coordinates (x, y)
   */
  e_terrain getTerrain(unsigned int x, unsigned int y);

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
   ** \return a pointer over the cells array
   */
  Cell **getCells();

  /** \brief sets the given unit in the cells array
   ** \param unit to set
   */
  void setUnit(Unit &u);

  /** \brief moves the selected unit to the current cursor location
   */
  void moveUnit();



private:
  unsigned int _nbColumns; ///< number of columns (x coordinate)
  unsigned int _nbLines; ///< number of lines (y coordinate)
  Cell **_cells; ///< Array which contains every cells of the map
};

#endif /* !MAP_HH_ */
