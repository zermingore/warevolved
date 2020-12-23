/**
 * \file
 * \date May 3, 2013
 * \author Zermingore
 * \brief Unit class definition
 */

#include <game/units/Unit.hh>

#include <debug/Debug.hh>
#include <graphics/Sprite.hh>
#include <game/Item.hh>
#include <game/Inventory.hh>



Unit::Unit()
  : _type(e_unit::NONE)
  , _played(false)
  , _moved(false)
  , _playerId(0)
  , _canHaveCrew(false)
  , _motionValue(0)
  , _hp(1)
  , _maxHp(_hp)
  , _attackValue(0)
  , _minRange(0)
  , _maxRange(0)
  , _inventory(std::make_shared<Inventory> ())
{
}



void Unit::setColor(const graphics::Color& color)
{
  _sprite->setColor(color);
}



bool Unit::addToCrew(std::shared_ptr<Unit> unit, e_unit_role role)
{
  ERROR("Invalid call to abstract Unit::addToCrew -> aborting...");
  ERROR("Called with",
        static_cast<int> (unit->type()),
        static_cast<int> (role));
  std::exit(1);
}
