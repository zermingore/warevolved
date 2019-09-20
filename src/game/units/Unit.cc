/**
 * \file
 * \date May 3, 2013
 * \author Zermingore
 * \brief Unit constructor definition
 */


#include <game/units/Unit.hh>

#include <debug/Debug.hh>
#include <graphics/Sprite.hh> // Sprite is forward-declared in the header



Unit::Unit()
  : _type(e_unit::NONE)
  , _played(false)
  , _moved(false)
  , _playerId(0)
  , _crewSize(0)
  , _canHaveCrew(false)
  , _motionValue(0)
  , _hp(1)
  , _maxHp(_hp)
  , _attackValue(0)
  , _minRange(0)
  , _maxRange(0)
{
}


void Unit::setColor(const graphics::Color& color)
{
  _sprite->setColor(color);
}


bool Unit::addToCrew(std::shared_ptr<Unit> unit)
{
  ERROR("Invalid call to Unit::addToCrew -> abort.");
  ERROR("Called with", static_cast<int> (unit->type()));
  std::exit(1);
}
