#include <interface/menus/InGameMenu.hh>
#include <interface/menus/MenuEntry.hh>
#include <common/globals.hh>
#include <common/macros.hh>


void InGameMenu::build(e_mode mode)
{
  init();

  // show unit section only if we selected a unit
  // here, we cannot use cursor's position, we could have move the unit
  auto current_unit(MAP.unit(g_status->selectedCell()));
  if (current_unit
      && current_unit->playerId() == g_status->currentPlayer()
      && !current_unit->played())
  {
    if (mode == E_MODE_SELECTION_MENU)
      _entries.emplace_back(MenuEntry("Move", E_ENTRY_MOVE));

    if (mode == E_MODE_ACTION_MENU)
      _entries.emplace_back(MenuEntry("Stop", E_ENTRY_STOP));
  }
  else
  {
    // next turn button
    _entries.emplace_back(MenuEntry("Next\n\tTurn", E_ENTRY_NEXT_TURN));
  }

  // target
  if (mode == E_MODE_ACTION_MENU)
    current_unit->fillActions(_entries);

  _entries.emplace_back(MenuEntry("Cancel", E_ENTRY_CANCEL));
  setOrigin();
}


void InGameMenu::executeEntry()
{
  (_entries)[_selectedEntry].execute();
  _selectedEntry = 0;
}
