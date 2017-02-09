#include <game/units/Unit.hh>
#include <game/Cell.hh>


Unit::Unit()
  : _played(false)
  , _playerId(0)
{
}

Unit::Unit(std::string &name)
  : Unit::Unit()
{
  _name = name;
}

void Unit::setCoords(const Coords location)
{
  _coords = location;
}
