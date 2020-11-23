/**
 * \file
 * \date October 25, 2020
 * \author Zermingore
 * \brief Building class declaration
 */

#ifndef BUILDING_HH_
# define BUILDING_HH_

# include <vector>
# include <memory>

# include <common/using.hh>

class Unit;



class Building
{
public:
  Building() = default;
  explicit Building(const std::vector<std::shared_ptr<Coords>> &coords) {
    _cells = coords;
  }

  ~Building() = default;


  ///< Units getter
  auto units()  { return _units; }

  ///< Coordinates getter
  auto getCoords() { return _cells; }

  /**
   * \brief Add the given Unit to the Building
   * \param unit Unit to add to the _units list
   * \note Change _factionControl if required
   */
  void addUnit(std::shared_ptr<Unit> unit);

  /**
   * \brief Remove the given unit from the Building
   * \param idx Index of the Unit in the _units vector
   */
  void removeUnit(size_t idx);

  /**
   * \brief Get the current faction controling the building
   * \return Faction number, matching player id
   */
  auto faction() { return _factionControl; }



private:
  int _factionControl = -1; ///< Who owns the building
  std::vector<std::shared_ptr<Coords>> _cells; ///< Map concerned Cells
  std::vector<std::shared_ptr<Unit>> _units; ///< Units in the building
  // std::vector<Floors> _floors; // Map list
  // std::vector<Item> _items; // Items inside the building
  // std::vector<Item> _collectable; // Ready to pick-up items
};


#endif // BUILDING_HH_
