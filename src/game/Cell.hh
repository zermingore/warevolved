#ifndef CELL_HH_
# define CELL_HH_

# include <game/Unit.hh>

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
  e_terrains getTerrain();

  /** \brief _unitTextureId getter
   ** \return cell's terrain texture id
   **   (in Resources Manager std::map)
   */
  unsigned int getUnitTextureId(); // TODO move in a Unit class

  /** \brief _terrainTextureId getter
   ** \return cell's terrain texture id
   **   (in Resources Manager std::map)
   */
  unsigned int getTerrainTextureId(); // TODO move in a Terrain class

  /** \brief _unit setter
   ** sets the unit \param unit in the cell
   **
   ** \param unit The unit to be set in the cell
   */
  void setUnit(Unit &unit);

  /** \brief _terrain setter
   ** sets the terrain \param terrain in the cell
   **
   ** \param terrain The terrain to be set in the cell
   */
  void setTerrain(const e_terrains terrain);

  /** \brief draws cell's contents: terrain and unit
   */
  void draw();



  // rm
  void printTimer();

private:
  Coords _coordinates; ///< cell's coordinates
  e_terrains _terrain; ///< Terrain type index (matching e_terrains)
  Unit *_unit; ///< Unit type index (matching e_terrains)
  unsigned int _terrainTextureId; ///< Terrain Texture id in the Resources Manager
  unsigned int _unitTextureId; ///< Unit Texture id in the Resources Manager

  unsigned int _IDTST; // rm
  std::vector<sf::Int64> res1, res2, res3;
};

#endif /* !CELL_HH_ */
