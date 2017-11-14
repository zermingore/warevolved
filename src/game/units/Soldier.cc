/**
 * \file
 * \date August 8, 2013
 * \author Zermingore
 * \brief Soldier class definition
 */

#include <game/units/Soldier.hh>

#include <graphics/Sprite.hh>



Soldier::Soldier()
  : Unit()
{
  _fullName = "John Doe";
  _sprite = std::make_shared<graphics::Sprite> ("soldiers");

  _motionValue = 3;
  _hp = 10;
  _attackValue = 5;

  _minRange = 1;
  _maxRange = 2;
}
