#ifndef CELL_HH_
# define CELL_HH_

# include <game/units/Unit.hh>
# include <common/enums/units.hh>
# include <common/enums/terrains.hh>

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
   **   without any Terrain (so no Texture either)
   **   without any Unit
   */
  Cell();

  /** \brief Destructor
   */
  ~Cell();

  /** \brief _unit getter
   ** \return cell's unit
   */
  Unit *getUnit();

  /** \brief _terrain getter
   ** \return cell's terrain
   */
  e_terrain getTerrain();

  /** \brief _unit setter
   ** sets the unit \param unit in the cell
   **
   ** \param unit The unit to be set in the cell
   */
  void setUnit(Unit &unit);

  /** \brief removes the unit in this cell
   */
  void removeUnit();

  /** \brief _terrain setter
   ** sets the terrain \param terrain in the cell
   **
   ** \param terrain The terrain to be set in the cell
   */
  void setTerrain(const e_terrain terrain);

  /** \brief _highlight setter
   ** \param highlight true if we want to highlight the cell
   */
  void setHighlight(bool highlight);

  /** \brief highlight color setter
   ** \param color color of the highlight of the cell
   */
  void setHighlightColor(Color color);


  /** \brief draws cell's contents: terrain and unit
   */
  void draw();


private:
  Coords _coordinates; ///< cell's coordinates
  e_terrain _terrain; ///< Terrain type index (matching e_terrains)
  Unit *_unit; ///< Unit type index (matching e_terrains)
  bool _highlight; ///< true if the cell needs to be highlighted
  Color _highlightColor; ///< color of the cell's highlight
};

#endif /* !CELL_HH_ */
