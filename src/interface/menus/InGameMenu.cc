#include <common/Status.hh>
#include <game/applications/Battle.hh>
#include <game/Player.hh>
#include <interface/menus/InGameMenu.hh>
#include <interface/menus/MenuEntry.hh>


namespace interface {


InGameMenu::InGameMenu()
{
  Debug::printf("Ctor");
}


void InGameMenu::build()
{
  // show unit section only if we selected a unit
  // here, we cannot use cursor's position, we could have move the unit
  // auto current_unit(MAP.unit(g_status->selectedCell()));
  // if (current_unit
  //     && current_unit->playerId() == g_status->currentPlayer()
  //     && !current_unit->played())
  // {
  //   if (state == state::SELECTION_MENU)
  //     _entries.emplace_back(MenuEntry("Move", entry::MOVE));

  //   if (state == state::ACTION_MENU)
  //     _entries.emplace_back(MenuEntry("Stop", entry::STOP));
  // }
  // else
  // {
  //   // next turn button
  //   _entries.emplace_back(MenuEntry("Next\n\tTurn", entry::NEXT_TURN));
  // }

  // target
  // if (state == state::ACTION_MENU)
  //   current_unit->fillActions(_entries);

  auto map(Status::battle()->map());
  if (map->unit(_coords))
  {
    Debug::printf("unit !");
    _entries.emplace_back(MenuEntry("tst", entry::CANCEL));
  }

  _entries.emplace_back(MenuEntry("Cancel", entry::CANCEL));
}


void InGameMenu::update(const std::shared_ptr<Map::MapGraphicsProperties> properties)
{
  auto width(properties->cellWidth());
  auto height(properties->cellHeight());

  // _coords is filled by the player, with cursor coordinates
  _position.x = _coords.x * width + properties->gridOffsetX() + width / 2;
  _position.y = _coords.y * height + properties->gridOffsetY() + height / 2;


//  for (const auto entry: _entries)


  Debug::printf("nb entries:", _entries.size());
  _image.sprite()->setOrigin(width / 2, height / 2);
  _image.sprite()->setScale(1, _entries.size());
}


} // namespace interface
