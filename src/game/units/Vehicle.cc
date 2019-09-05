
/**
 * \file
 * \date September 5, 2019
 * \author Zermingore
 * \brief Vehicle (specific Unit) abstract class definition
 */

#include <game/units/Vehicle.hh>

#include <debug/Debug.hh>
#include <game/Status.hh>
#include <game/Battle.hh>
#include <game/Map.hh>



bool Vehicle::dropOff(e_unit_role role, Coords location)
{
  if (_crewSize == 0)
  {
    ERROR("Called 'dropOff()' with an empty Vehicle");
    return false;
  }

  if (_crew.find(role) == _crew.end())
  {
    ERROR("Role not occupied in the Vehicle");
    return false;
  }

  auto map = game::Status::battle()->map();
  if (map->unit(location) != nullptr)
  {
    /// \todo hanle transfer unit from one vehicle to another one
    ERROR("Called 'dropOff()' with an occupied location");
    return false;
  }

  auto unit = _crew.at(role);
  map->revealUnit(*unit);

  ERROR("[IMPLEMENTATION ERROR] Failed trying to add the unit to the crew");
  return false;
}
