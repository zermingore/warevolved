#ifndef CELL_HH_
# define CELL_HH_

# include <common/units.hh>
# include <common/terrains.hh>

/** \brief Cell class: the simplest element of a map
 **   we can see a Map as a grid, an array of array, of Cell
 **
 ** a Cell has:
 **   a terrain
 **   eventually, a unit
 */

class Cell
{
public:
  /** \brief Default Constructor creates an empty Cell
   */
  Cell();

  /** \brief Destructor
   */
  ~Cell();

  /** \brief _unit getter
   ** \return cell's unit
   */
  e_units getUnit();

  /** \brief _terrain getter
   ** \return cell's terrain
   */
  e_terrains getTerrain();

  // _________________________ SETTERS _________________________ //
  /** \brief _unit setter
   ** setts the unit \param unit in the cell
   **
   ** \param unit The unit to be set in the cell
   */
  void setUnit(e_units unit);

  /** \brief _terrain setter
   ** setts the terrain \param terrain in the cell
   **
   ** \param terrain The terrain to be set in the cell
   */
  void setTerrain(e_terrains terrain);


private:
  e_terrains _terrain; ///< Terrain type index (matching e_terrains)
  e_units _unit; ///< Unit type index (matching e_terrains)
};

#endif /* !CELL_HH_ */
