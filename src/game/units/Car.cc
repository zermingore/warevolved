/**
 * \file
 * \date August 1, 2019
 * \author Zermingore
 * \brief Car (specific Unit) class definition
 */

#include <game/units/Car.hh>

#include <debug/Debug.hh>
#include <graphics/Sprite.hh>
#include <game/units/UnitsFactory.hh>



Car::Car()
  : Vehicle()
{
  _type = e_unit::CAR;

  /// \todo Multiple sprites
  _sprite = std::make_shared<graphics::Sprite> ("car");

  _motionValue = 5;
  _maxHp = UnitsFactory::typeMaxHp(_type);
  _hp = _maxHp;
  _attackValue = 0;

  _minRange = 0;
  _maxRange = 0;

  _maxCrewMembers = 5;

  /// \todo Initialize the map
  // The keys should stay constant; only the values are adjusted
  // _crew[e_unit_role::DRIVER] = nullptr;
  // _crew[e_unit_role::COPILOT] = nullptr;
  // _crew[e_unit_role::PASSENGER] = nullptr;
}



bool Car::canOpenFire() const
{
  return _crew.find(e_unit_role::COPILOT) != _crew.end();
}



bool Car::addToCrew(std::shared_ptr<Unit> unit, e_unit_role role)
{
  if (_crew.size() >= _maxCrewMembers)
  {
    ERROR("Called 'addToCrew()' with a full Vehicle");
    return false;
  }

  // If the role is specified, use it
  if (role != e_unit_role::NONE)
  {
    if (_crew.contains(role))
    {
      WARNING("Already occupied role", static_cast<int> (role));
      return false;
    }

    _crew[role].push_back(unit);
    return true;
  }


  std::shared_ptr<Unit> driver = nullptr;
  std::shared_ptr<Unit> copilot = nullptr;

  if (!_crew.contains(e_unit_role::DRIVER))
  {
    _crew[e_unit_role::DRIVER].push_back(unit);
    return true;
  }
  if (!_crew.contains(e_unit_role::COPILOT))
  {
    _crew[e_unit_role::COPILOT].push_back(unit);
    return true;
  }

  ERROR("[IMPLEMENTATION ERROR] Failed trying to add the unit to the crew");
  return false;
}
