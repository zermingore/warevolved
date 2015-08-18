#include <interface/menus/InGameMenu.hh>
#include <interface/menus/MenuEntry.hh>


void InGameMenu::build(mode mode)
{
  init();

  // show unit section only if we selected a unit
  // here, we cannot use cursor's position, we could have move the unit
  // auto current_unit(MAP.unit(g_status->selectedCell()));
  // if (current_unit
  //     && current_unit->playerId() == g_status->currentPlayer()
  //     && !current_unit->played())
  // {
  //   if (mode == mode::SELECTION_MENU)
  //     _entries.emplace_back(MenuEntry("Move", entry::MOVE));

  //   if (mode == mode::ACTION_MENU)
  //     _entries.emplace_back(MenuEntry("Stop", entry::STOP));
  // }
  // else
  // {
  //   // next turn button
  //   _entries.emplace_back(MenuEntry("Next\n\tTurn", entry::NEXT_TURN));
  // }

  // target
  // if (mode == mode::ACTION_MENU)
  //   current_unit->fillActions(_entries);

  _entries.emplace_back(MenuEntry("Cancel", entry::CANCEL));
  setOrigin();
}


void InGameMenu::executeEntry()
{
  (_entries)[_selectedEntry].execute();
  _selectedEntry = 0;
}
