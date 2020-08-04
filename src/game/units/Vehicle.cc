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



void Vehicle::dropOff(e_unit_role role, const Coords& location)
{
  assert(!_crew.empty() && "Called 'dropOff()' with an empty Vehicle");
  assert(_crew.find(role) != _crew.end() && "Role not found in the Vehicle");

  auto map = game::Status::battle()->map();
  assert(   map->unit(location) == nullptr
         && "Called 'dropOff()' with an occupied location");

  auto unit = _crew.at(role);
  unit->setCoords(location);
  map->stashPopUnit(*unit);
  _crew.erase(role);

  _dropped[role] = unit;
}


void Vehicle::restoreCrew()
{
  for (const auto& member: _dropped)
  {
    /// \todo Make sure the roles are properly restored
    addToCrew(member.second);
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
