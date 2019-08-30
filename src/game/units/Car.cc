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
}



bool Car::canOpenFire()
{
  return _crew[e_unit_role::COPILOT] != nullptr;
}



bool Car::addToCrew(std::shared_ptr<Unit> unit)
{
  std::shared_ptr<Unit> driver = nullptr;
  std::shared_ptr<Unit> copilot = nullptr;
  try
  {
    driver = _crew.at(e_unit_role::DRIVER);
    copilot = _crew.at(e_unit_role::COPILOT);
  }
  catch (std::out_of_range& e)
  {
    if (copilot)
    {
      NOTICE("Driver and Copilot already on board");
      return false;
    }

    if (driver)
    {
      _crew[e_unit_role::COPILOT] = unit;
      return true;
    }
    else // empty car
    {
      _crew[e_unit_role::DRIVER] = unit;
      return true;
    }
  }


  ERROR("IMPLEMENTATION ERROR Trying to add the given unit");

  return false;
}
