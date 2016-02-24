#include <game/units/Soldier.hh>


Soldier::Soldier()
{
  _name = "soldiers";
  _fullName = "John Doe";
  _imageId = 0;
  _hp = 15;
  _attackValue = 10;
  _range = std::make_pair(0, 3);
  _motionValue = 4;
  _played = false;
  _playerId = 0;
}


 /// \todo move into Map
void Soldier::fillActions(std::vector<MenuEntry>& menu)
{
  menu = menu;
   /// \todo add inventory entry

  // checks if we must add the 'Attack' entry
  // for (auto c: *_targets)
  // {
  //   // Manhattan distance
  //   auto manhattan = std::abs((int) CURSOR->x() - (int) c->x()) +
  //     std::abs((int) CURSOR->y() - (int) c->y());
  //   if (manhattan > _range.first && manhattan < _range.second)
  //   {
  //     menu.emplace_back(MenuEntry("Attack", entry::attack));
  //     break; // we do not need to add the entry multiple times
  //   }
  // }
}
