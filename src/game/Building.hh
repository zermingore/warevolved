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
  auto getUnits()  { return _units; }

  ///< Coordinates getter
  auto getCoords() { return _cells; }


  void addUnit(std::shared_ptr<Unit> unit);


private:
  std::vector<std::shared_ptr<Coords>> _cells; ///< Map concerned Cells
  std::vector<std::shared_ptr<Unit>> _units; ///< Units in the building
  // std::vector<Floors> _floors; // Map list
  // std::vector<Item> _items; // Items inside the building
  // std::vector<Item> _collectable; // Ready to pick-up items
};


#endif // BUILDING_HH_
