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

class Cell;
class Unit;



class Building
{
private:
  std::vector<std::shared_ptr<Cell>> _cells; ///< Map concerned Cells
  std::vector<std::shared_ptr<Unit>> _units; ///< Units in the building
  // std::vector<Floors> _floors; // Map list
  // std::vector<Item> _items; // Items inside the building
  // std::vector<Item> _collectable; // Ready to pick-up items
};


#endif // BUILDING_HH_
