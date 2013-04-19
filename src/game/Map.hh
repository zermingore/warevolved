#ifndef MAP_HH_
# define MAP_HH_

# include <common/include.hh>
# include <common/units.hh>
# include <common/terrains.hh>
# include <game/Cell.hh>


/** \brief class which represents the game map
 */

class Map
{
public:
  /** \brief Default Constructor
   */
  Map();

  /** \brief Constructs a map of nbColumns x nbLines
   ** \param nbColumns Number of columns required
   ** \param nbLines Number of lines required
   */
  Map(unsigned int nbColumns, unsigned int nbLines);

  /** \brief Default Destructor
   */
  ~Map();


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
  e_units getUnit(unsigned int x, unsigned int y);


  /** \brief gets the terrain at coordinates (x, y)
   **
   ** \param x Coordinates according to columns
   ** \param y Coordinates according to lines
   **
   ** \return the enum index in e_terrain matching the terrain
   **   located at coordinates (x, y)
   */
  e_terrains getTerrain(unsigned int x, unsigned int y);

private:
  unsigned int _nbColumns; ///< number of columns (x coordinate)
  unsigned int _nbLines; ///< number of lines (y coordinate)

  Cell* _cells;
};

#endif /* !MAP_HH_ */
