/**
 * \file
 * \date August 1, 2019
 * \author Zermingore
 * \brief Car (specific Unit) class definition
 */

#include <game/units/Car.hh>

#include <debug/Debug.hh>
#include <graphics/Sprite.hh>



Car::Car()
  : Vehicle()
{
  _type = e_unit::CAR;
  _sprite = std::make_shared<graphics::Sprite> ("car"); // TODO multiple sprites

  _motionValue = 5;
  _hp = 30;
  _maxHp = _hp;
  _attackValue = 0;

  _minRange = 0;
  _maxRange = 0;

  _maxCrewMembers = 5;
  _crewSize = 0;
}



bool Car::canOpenFire()
{
  return _crew.find(e_unit_role::COPILOT) != _crew.end();
}



bool Car::addToCrew(std::shared_ptr<Unit> unit)
{
  if (_crewSize >= _maxCrewMembers)
  {
    ERROR("Called 'addToCrew()' with a full Vehicle");
    return false;
  }

  std::shared_ptr<Unit> driver = nullptr;
  std::shared_ptr<Unit> copilot = nullptr;
  try
  {
    driver = _crew.at(e_unit_role::DRIVER);
    copilot = _crew.at(e_unit_role::COPILOT);
  }
  catch (const std::out_of_range& e)
  {
    if (copilot) /// \todo Take into account passengers
    {
      NOTICE("Driver and Copilot already on board");
      return false;
    }

    if (driver)
    {
      _crew[e_unit_role::COPILOT] = unit;
      ++_crewSize;
      return true;
    }
    else // empty car
    {
      _crew[e_unit_role::DRIVER] = unit;
      ++_crewSize;
      return true;
    }
  }

  ERROR("[IMPLEMENTATION ERROR] Failed trying to add the unit to the crew");
  return false;
}
