#include <game/units/Soldier.hh>


Soldier::Soldier()
  : Unit()
{
  _fullName = "John Doe";
  _image = resources::ResourcesManager::getImage("soldiers");
}
