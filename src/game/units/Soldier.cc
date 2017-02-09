#include <game/units/Soldier.hh>


Soldier::Soldier()
  : Unit()
{
  _name = "soldiers"; /// \todo do not use name here, move into a factory
  _fullName = "John Doe";
}
