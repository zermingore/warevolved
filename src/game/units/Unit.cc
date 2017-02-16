#include <game/units/Unit.hh>
#include <game/Cell.hh>


Unit::Unit()
  : _played(false)
  , _playerId(0)
  , _hp(1)
  , _motionValue(0)
  , _attackValue(0)
{
}
