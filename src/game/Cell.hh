/**
 * \file
 * \date April 19, 2013
 * \author Zermingore
 */

#ifndef CELL_HH_
# define CELL_HH_

# include <game/units/Unit.hh>

enum class e_terrain;
enum class e_unit;


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
  /// Deleted default constructor.
  Cell() = delete;

  /**
   * \brief Constructor. Creates an empty Cell at given coordinates.
   *
   * Draw the cell without any Terrain (so no Texture either).
   * and without any Unit.
   *
   * \param c column coordinate of the cell to create.
   * \param l line   coordinate of the cell to create.
   */
  Cell(size_t c, size_t l);

  // __________________________ Getters / Setters __________________________ //
  /**
   * \brief _unit getter.
   * \return cell's unit.
   */
  std::shared_ptr<Unit> unit() { return _unit; }

  /**
   * \brief _terrain getter.
   * \return cell's terrain.
   */
  e_terrain terrain() { return _terrain; }

  /**
   * \brief _unit setter. Sets the given Unit in the cell.
   * \param unit The unit to be set in the cell.
   */
  void setUnit(std::shared_ptr<Unit> unit) { _unit = unit; }

  /**
   * \brief Sets the given terrain in the Cell.
   * \param terrain The terrain to be set in the Cell.
   */
  void setTerrain(const e_terrain terrain) { _terrain = terrain; }

  /**
   * \brief Highlight getter.
   * \return Highlight Boolean value.
   */
  bool highlight() { return _highlight; }

  /**
   * \brief Highlight setter.
   * \param Highlight true if we want to highlight the Cell.
   */
  void setHighlight(bool highlight) { _highlight = highlight; }

  /**
   * \brief Highlight color getter.
   * \return Highlight color value.
   */
  Color highlightColor() { return _highlightColor; }

  /**
   * \brief Highlight color setter.
   * \param color Color of Cell's highlight.
   */
  void setHighlightColor(Color color) { _highlightColor = color; }

  /**
   * \brief Removes the unit in this cell.
   */
  void removeUnit() { _unit = nullptr; }

  /**
   * \brief returns Cell's x coordinate.
   * \return cell x coordinate.
   */
  size_t x() { return _coords.x; }

  /**
   * \brief returns Cell's y coordinate.
   * \return cell y coordinate.
   * \note l: line
   */
  size_t l() { return _coords.x; }

  /**
   * \brief returns Cell's y coordinate.
   * \return cell y coordinate.
   */
  size_t y() { return _coords.y; }

  /**
   * \brief returns Cell's x coordinate.
   * \return cell x coordinate.
   * \note c: column
   */
  size_t c() { return _coords.y; }

  /**
   * \brief coords getter.
   */
  Coords coords() { return _coords; }


private:
  Coords _coords;              ///< Cell's coordinates.
  e_terrain _terrain;          ///< Terrain type index (matching terrains).
  std::shared_ptr<Unit> _unit; ///< Unit type index (matching terrains).

  bool _highlight;       ///< True if the cell needs to be highlighted.
  Color _highlightColor; ///< Color of the cell's highlight.
};

#endif /* !CELL_HH_ */
