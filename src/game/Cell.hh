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

  // __________________________ Getters / Setters __________________________ //
  /** \brief _unit getter
   ** \return cell's unit
   */
  inline std::shared_ptr<Unit> unit() { return _unit; }

  /** \brief _terrain getter
   ** \return cell's terrain
   */
  inline e_terrain getTerrain() { return _terrain; }

  /** \brief _unit setter
   ** sets the Unit \param unit in the cell
   ** \param unit The unit to be set in the cell
   */
  inline void setUnit(std::shared_ptr<Unit> unit) { _unit = unit; }

  /** \brief _terrain setter
   ** sets the terrain \param terrain in the Cell
   **
   ** \param terrain The terrain to be set in the Cell
   */
  inline void setTerrain(const e_terrain terrain) { _terrain = terrain; }

  /** \brief _highlight setter
   ** \param highlight true if we want to highlight the Cell
   */
  inline void setHighlight(bool highlight) { _highlight = highlight; }

  /** \brief highlight color setter
   ** \param color color of Cell's highlight
   */
  inline void setHighlightColor(Color color) { _highlightColor = color; }


  /** \brief removes the unit in this cell
   */
  inline void removeUnit() { _unit = nullptr; }

  /** \brief draws Cell's contents: terrain and unit
   */
  void draw();

  /** \brief returns Cell's x coordinate
   */
  inline unsigned int x() { return _coordinates.x; }

  /** \brief returns Cell's y coordinate
   */
  inline unsigned int y() { return _coordinates.y; }


private:
  Coords _coordinates; ///< cell's coordinates
  e_terrain _terrain; ///< Terrain type index (matching e_terrains)
  std::shared_ptr<Unit> _unit; ///< Unit type index (matching e_terrains)
  bool _highlight; ///< true if the cell needs to be highlighted
  Color _highlightColor; ///< color of the cell's highlight
};

#endif /* !CELL_HH_ */
