#include <game/units/Soldier.hh>


Soldier::Soldier()
  : Unit()
{
  _fullName = "John Doe";
  _image = resources::ResourcesManager::getImage("soldiers");

  _hp = 10;
  _motionValue = 3;
  _attackValue = 5;
}
