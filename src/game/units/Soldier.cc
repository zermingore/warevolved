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

  // Inventory dependent
  _attackValue = 1;
  _minRange = 1;
  _maxRange = 1;

  _inventory->addContainer(e_container_type::EQUIPPED, "Equipped", 0, 0);
  _inventory->addContainer(
    e_container_type::POCKET, "trousers\npocket left", 10, 5);
  _inventory->addContainer(
    e_container_type::POCKET, "Trousers\npocket right", 1, 1);
}



size_t Soldier::minRange() const
{
  try
  {
    return *(_inventory->range()[e_item_slot::MAIN_WEAPON].second);
  }
  catch (const std::out_of_range& e)
  {
    return _minRange;
  }
}



size_t Soldier::maxRange() const
{
  try
  {
    return *(_inventory->range()[e_item_slot::MAIN_WEAPON].second);
  }
  catch (const std::out_of_range& e)
  {
    return _maxRange;
  }
}
