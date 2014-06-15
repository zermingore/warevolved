#include <common/enums/ranks.hh>
#include <game/units/Soldier.hh>
#include <common/globals.hh>

Soldier::Soldier() :
  _equipedWeapon (nullptr),
  _rank (E_RANK_PRIVATE)
{
  _name = "soldiers";
  _fullName = "John Doe";
  _imageId = 0;
  _hp = 0;
  _posX = 0;
  _posY = 0;
  _cellX = 1;
  _cellY = 1;
  _motionValue = 4;
  _played = false;
  _playerId = 0;
}
