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
    {
      auto move = MenuEntry("Move", E_ENTRY_MOVE);
      _entries.push_back(move);
    }
    if (mode == E_MODE_ACTION_MENU)
    {
      auto stop = MenuEntry("Stop", E_ENTRY_STOP);
      _entries.push_back(stop);
    }
  }
  else
  {
    // next turn button
    auto next_turn = MenuEntry("Next\n\tTurn", E_ENTRY_NEXT_TURN);
    _entries.push_back(next_turn);
  }

  // target
  if (mode == E_MODE_ACTION_MENU
      && MAP.unit(CURSOR->x(), CURSOR->y()))
  {
    auto attack = MenuEntry("Attack", E_ENTRY_ATTACK);
    _entries.push_back(attack);
  }

  auto cancel = MenuEntry("Cancel", E_ENTRY_CANCEL);
  _entries.push_back(cancel);

  _nbEntries = _entries.size();
  setOrigin();
}


void InGameMenu::executeEntry()
{
  (_entries)[_selectedEntry].execute();
  _selectedEntry = 0;
}
