#include <common/Status.hh>
#include <game/applications/Battle.hh>
#include <game/Player.hh>
#include <interface/menus/InGameMenu.hh>
#include <interface/menus/MenuEntry.hh>


namespace interface {



void InGameMenu::build()
{
  // Clearing entries content
  //_entries.clear();

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

  // auto interface(Status::interface());
  auto map(Status::battle()->map());
  if (map->unit(_coords))
  {
    auto entry(std::make_shared<MenuEntry> (e_entry::MOVE));
    _entries.push_back(entry);
    Status::interface()->addElement(entry);
  }

  Debug::printf("Adding entry");
  auto entry(std::make_shared<MenuEntry> (e_entry::CANCEL));
  _entries.push_back(entry);
  Status::interface()->addElement(entry);
}



void InGameMenu::update(const std::shared_ptr<Map::MapGraphicsProperties> properties)
{
  auto width(properties->cellWidth());
  auto height(properties->cellHeight());

  // _coords is filled by the player, with cursor coordinates
  _position.x = _coords.x * width  + properties->gridOffsetX();
  _position.y = _coords.y * height + properties->gridOffsetY();

  // update entries positions
  auto entry_index(0);
  for (auto entry: _entries)
  {
    entry->setPosition(Coords(_position.x, _position.y + height * entry_index));
    ++entry_index;
  }
}


void InGameMenu::close()
{
  auto interface(Status::interface());
  for (auto entry: _entries) {
    interface->removeElement(entry);
  }
  // interface->removeElement(this); // apparently not needed, not sure why

  interface->setCurrentMenu(nullptr);
}


} // namespace interface
