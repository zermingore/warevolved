#include <common/Status.hh>
#include <game/applications/Battle.hh>
#include <game/Player.hh>
#include <interface/menus/InGameMenu.hh>
#include <interface/menus/MenuEntry.hh>


namespace interface {

InGameMenu::InGameMenu()
  : InterfaceElement("selection_menu_button")
{
}


void InGameMenu::build(/* e_state state */)
{
  //init();

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

  //_entries.emplace_back(MenuEntry("Cancel", entry::CANCEL));
  //setOrigin();
}


void InGameMenu::executeEntry()
{
//  (_entries)[_selectedEntry].execute();
//  _selectedEntry = 0;
}


void InGameMenu::update(const std::shared_ptr<Map::MapGraphicsProperties> properties)
{
  auto width(properties->cellWidth());
  auto height(properties->cellHeight());

  // coords is filled by the player, with cursor coordinates
  _position.x = _coords.x * width + properties->gridOffsetX() + width / 2;
  _position.y = _coords.y * height + properties->gridOffsetY() + height / 2;

  _image.sprite()->setOrigin(width / 2, height / 2);
}


} // namespace interface
