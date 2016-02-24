#ifndef CELL_HH_
# define CELL_HH_

# include <game/units/Unit.hh>
# include <common/enums/units.hh>
# include <common/enums/terrains.hh>

/**
 * \class Cell
 * \brief The element of a map.
 *
 * A Map can be seen as a grid, an array of array of Cell.
 *
 * A Cell has:
 *   a terrain
 *   eventually, a unit
 */
class Cell
{
public:
  /**
   * \brief deleted default constructor
   */
  Cell() = delete;

  /**
   * \brief Constructor: creates an empty Cell
   *   at coordinates x, y
   *   without any Terrain (so no Texture either)
   *   without any Unit
   */
  Cell(size_t x, size_t y);

  // __________________________ Getters / Setters __________________________ //
  /**
   * \brief _unit getter
   * \return cell's unit
   */
  std::shared_ptr<Unit> unit() { return _unit; }

  /**
   * \brief _terrain getter
   * \return cell's terrain
   */
  e_terrain terrain() { return _terrain; }

  /**
   * \brief _unit setter
   * sets the Unit \param unit in the cell
   * \param unit The unit to be set in the cell
   */
  void setUnit(std::shared_ptr<Unit> unit) { _unit = unit; }

  /**
   * \brief Sets the given terrain in the Cell.
   * \param terrain The terrain to be set in the Cell.
   */
  void setTerrain(const e_terrain terrain) { _terrain = terrain; }

  /**
   * \brief _highlight getter
   * \return highlight Boolean value
   */
  bool highlight() { return _highlight; }

  /**
   * \brief _highlight setter
   * \param highlight true if we want to highlight the Cell
   */
  void setHighlight(bool highlight) { _highlight = highlight; }

  /**
   * \brief highlight color getter
   * \return highlight color value
   */
  Color highlightColor() { return _highlightColor; }

  /**
   * \brief highlight color setter
   * \param color color of Cell's highlight
   */
  void setHighlightColor(Color color) { _highlightColor = color; }

  /**
   * \brief removes the unit in this cell
   */
  void removeUnit() { _unit = nullptr; }

  /**
   * \brief returns Cell's x coordinate
   */
  unsigned int x() { return _coords.x; }

  /**
   * \brief returns Cell's y coordinate
   */
  unsigned int y() { return _coords.y; }

  /**
   * \brief coords getter
   */
  Coords coords() { return _coords; }


private:
  Coords _coords;              ///< cell's coordinates
  e_terrain _terrain;          ///< Terrain type index (matching terrains)
  std::shared_ptr<Unit> _unit; ///< Unit type index (matching terrains)

  bool _highlight;       ///< true if the cell needs to be highlighted
  Color _highlightColor; ///< color of the cell's highlight
};

#endif /* !CELL_HH_ */
