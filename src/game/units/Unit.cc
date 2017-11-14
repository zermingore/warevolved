/**
 * \file
 * \date May 3, 2013
 * \author Zermingore
 * \brief Unit constructor definition
 *
 * The Unit constructor is used to delegate a part of the initialization
 */


#include <game/units/Unit.hh>

#include <graphics/Sprite.hh> // Sprite is forward-declared in the header



Unit::Unit()
  : _played(false)
  , _playerId(0)
  , _motionValue(0)
  , _hp(1)
  , _attackValue(0)
  , _minRange(0)
  , _maxRange(0)
{
}
