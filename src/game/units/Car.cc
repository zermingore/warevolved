/**
 * \file
 * \date August 1, 2019
 * \author Zermingore
 * \brief Car (specific Unit) class definition
 */

#include <game/units/Car.hh>

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
