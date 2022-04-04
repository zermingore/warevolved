/**
 * \file
 * \date October 28, 2020
 * \author Zermingore
 * \brief Building class implementation
 */

#include <game/Building.hh>

#include <game/units/Unit.hh>



void Building::addUnit(std::shared_ptr<Unit> unit)
{
  _units.push_back(unit);
  _factionControl = static_cast<int> (unit->playerId());
}



void Building::removeUnit(size_t idx)
{
  _units.erase(_units.begin() + static_cast<int> (idx));
  if (_units.size() == 0)
  {
    _factionControl = -1;
  }
}
