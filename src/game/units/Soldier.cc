#include <game/units/Soldier.hh>


Soldier::Soldier()
  : Unit()
{
  _fullName = "John Doe";
  _image = resources::ResourcesManager::getImage("soldiers");

  _motionValue = 11;
  _hp = 10;
  _attackValue = 5;

  _minRange = 4;
  _maxRange = 7;
}
