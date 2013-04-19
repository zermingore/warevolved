#ifndef CELL_HH_
# define CELL_HH_

# include <common/units.hh>
# include <common/terrains.hh>


class Cell
{
public:
  /** \brief Default Constructor creates an empty Cell
   */
  Cell();

  /** \brief Default Destructor
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
