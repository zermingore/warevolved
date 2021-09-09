/**
 * \file
 * \date August 8, 2013
 * \author Zermingore
 * \brief Soldier (specific Unit) class definition
 */

#include <game/units/Soldier.hh>

#include <game/units/UnitsFactory.hh>
#include <game/Inventory.hh>
#include <graphics/Sprite.hh>



Soldier::Soldier()
{
  _type = e_unit::SOLDIER;
  _sprite = std::make_shared<graphics::Sprite> ("soldier");

  _motionValue = 3;
  _maxHp = UnitsFactory::typeMaxHp(_type);
  _hp = _maxHp;
  _attackValue = 5;

  _minRange = 1;
  _maxRange = 2;

  _inventory->addContainer(e_container_type::EQUIPPED, "Equipped", -1, -1);
  _inventory->addContainer(
    e_container_type::POCKET, "trousers\npocket left", 5, 10);
  _inventory->addContainer(
    e_container_type::POCKET, "Trousers\npocket right", 5, 10);
}
