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
  explicit Building(const std::vector<Coords> &coords) {
    _cells = coords;
  }

  ~Building() = default;


private:
  std::vector<Coords> _cells; ///< Map concerned Cells
  // std::unique_ptr<std::vector<Unit>> _units; ///< Units in the building
  // std::vector<Floors> _floors; // Map list
  // std::vector<Item> _items; // Items inside the building
  // std::vector<Item> _collectable; // Ready to pick-up items
};


#endif // BUILDING_HH_
