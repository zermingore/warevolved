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
  _hp = 10;
  _attackValue = 25;
  _range = std::make_pair(0, 2);
  _motionValue = 4;
  _played = false;
  _playerId = 0;
}


void Soldier::fillActions(std::vector<MenuEntry>& menu)
{
  // TODO add inventory entry

  auto unit = MAP.unit(CURSOR->x(), CURSOR->y());
  // if (!unit) // no Unit on this Cell
  //   return;

  // the Unit is targeting itself or a teammate
  // if (unit.get() == this || unit->playerId() == _playerId)
  //   return;

  for (auto c: *(g_status->targetsList()))
  {
    // Manhattan distance
    if (std::abs((int) CURSOR->x() - (int) _cellX) +
        std::abs((int) CURSOR->y() - (int) _cellY) < 3)
    {
      menu.emplace_back(MenuEntry("Attack", E_ENTRY_ATTACK));
      break; // we do not need to add the entry multiple times
    }
  }
}
