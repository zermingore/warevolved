/**
 * \file
 * \date September 5, 2019
 * \author Zermingore
 * \brief Vehicle (specific Unit) abstract class definition
 */

#include <game/units/Vehicle.hh>

#include <context/State.hh>
#include <debug/Debug.hh>
#include <game/Battle.hh>
#include <game/Map.hh>
#include <game/Status.hh>



Vehicle::Vehicle()
{
  _canHaveCrew = true;
}



void Vehicle::dropOff(size_t crew_index, const Coords& location)
{
  assert(!_crew.empty() && "Called 'dropOff()' with an empty Vehicle");
  std::shared_ptr<Unit> unit { _crew[crew_index].second };

  auto map = game::Status::battle()->map();
  assert(   map->unit(location) == nullptr
         && "Called 'dropOff()' with an occupied location");

  unit->setCoords(location);
  map->stashPopUnit(*unit);

  _dropped.push_back(_crew[crew_index]);
  _crew.erase(_crew.begin() + crew_index);
}



void Vehicle::restoreCrew()
{
  for (const auto& member: _dropped)
  {
    addToCrew(member.second, member.first);
    game::Status::battle()->map()->stashUnit(*(member.second));
  }
}



bool Vehicle::canReceive(const std::shared_ptr<const Unit> unit) const
{
  if (unit->type() != e_unit::SOLDIER)
  {
    return false;
  }

  return _crew.size() < _maxCrewMembers;
}
