#include <game/units/Soldier.hh>
#include <graphics/Sprite.hh>


Soldier::Soldier()
  : Unit()
{
  _fullName = "John Doe";
  _sprite = std::make_shared<graphics::Sprite> ("soldiers");

  _motionValue = 13;
  _hp = 1;
  _attackValue = 5;

  _minRange = 1;
  _maxRange = 2;
}
