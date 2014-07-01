#include <common/enums/ranks.hh>
#include <game/units/Soldier.hh>
#include <common/globals.hh>


Soldier::Soldier() :
  _equipedWeapon (nullptr)
{
  static int id = 0;

  _class = "soldiers";
  _name = g_text->getName(id++);
  _imageId = 0;
  _hp = 15;
  _maxHp = _hp;
  _attackValue = 10;
  _range = std::make_pair(0, 3);
  _motionValue = 4;
  _playerId = 0;
}


void Soldier::fillActions(std::vector<MenuEntry>& menu)
{
  // TODO add inventory entry

  // checks if we must add the 'Attack' entry
  for (auto c: *_targets)
  {
    // Manhattan distance
    auto manhattan = std::abs((int) CURSOR->x() - (int) c->x()) +
      std::abs((int) CURSOR->y() - (int) c->y());
    if (manhattan > _range.first && manhattan < _range.second)
    {
      menu.emplace_back(MenuEntry("Attack", E_ENTRY_ATTACK));
      break; // we do not need to add the entry multiple times
    }
  }
}
