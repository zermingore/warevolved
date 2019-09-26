/**
 * \file
 * \date August 8, 2013
 * \author Zermingore
 * \brief Soldier (specific Unit) class definition
 */

#include <game/units/Soldier.hh>

#include <graphics/Sprite.hh>



Soldier::Soldier()
  : Unit()
{
  _type = e_unit::SOLDIER;
  _sprite = std::make_shared<graphics::Sprite> ("soldier");

  _motionValue = 3;
  _hp = 10;
  _maxHp = _hp;
  _attackValue = 5;

  _minRange = 1;
  _maxRange = 2;
}
