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
#include <common/enums/states.hh>
#include <context/State.hh>



Vehicle::Vehicle()
  : Unit()
{
  _canHaveCrew = true;
}



void Vehicle::dropOff(e_unit_role role, Coords location)
{
  assert(_crew.size() != 0 && "Called 'dropOff()' with an empty Vehicle");
  assert(_crew.find(role) != _crew.end() && "Role not found in the Vehicle");

  auto map = game::Status::battle()->map();
  assert(   map->unit(location) == nullptr
         && "Called 'dropOff()' with an occupied location");

  auto unit = _crew.at(role);
  unit->setCoords(location);
  map->revealUnit(*unit);
  _crew.erase(role);
}
