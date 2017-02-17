#include <game/units/Unit.hh>
#include <game/Cell.hh>


Unit::Unit()
  : _played(false)
  , _playerId(0)
  , _motionValue(0)
  , _hp(1)
  , _attackValue(0)
  , _minRange(1) // at the moment, forbidding to have 2 units on the same cell
  , _maxRange(0)
{
}
