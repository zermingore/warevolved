/**
 * \file
 * \date March 20, 2020
 * \author Zermingore
 * \brief Motorcycle (specific Unit) class definition
 */

#include <game/units/Motorcycle.hh>

#include <debug/Debug.hh>
#include <graphics/Sprite.hh>
#include <game/units/UnitsFactory.hh>



Motorcycle::Motorcycle()
  : Vehicle()
{
  _type = e_unit::MOTORCYCLE;

  /// \todo Multiple sprites
  _sprite = std::make_shared<graphics::Sprite> ("motorcycle");

  _motionValue = 5;
  _maxHp = UnitsFactory::typeMaxHp(_type);
  _hp = _maxHp;
  _attackValue = 0;

  _minRange = 0;
  _maxRange = 0;

  _maxCrewMembers = 1;

  /// \todo Initialize the map
  // The keys should stay constant; only the values are adjusted
  // _crew[e_unit_role::DRIVER] = nullptr;
}



bool Motorcycle::canOpenFire()
{
  return !_crew.empty();
}



bool Motorcycle::addToCrew(std::shared_ptr<Unit> unit)
{
  if (_crew.size() >= _maxCrewMembers)
  {
    ERROR("Called 'addToCrew()' with a full Vehicle");
    return false;
  }

  std::shared_ptr<Unit> driver = nullptr;
  std::shared_ptr<Unit> copilot = nullptr;

  if (!_crew.contains(e_unit_role::DRIVER))
  {
    _crew[e_unit_role::DRIVER] = unit;
    return true;
  }

  ERROR("[IMPLEMENTATION ERROR] Failed trying to add the unit to the crew");
  return false;
}
