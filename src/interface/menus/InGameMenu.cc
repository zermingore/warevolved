#include <interface/menus/InGameMenu.hh>
#include <interface/menus/MenuEntry.hh>
#include <common/globals.hh>
#include <common/macros.hh>


InGameMenu::InGameMenu() :
  _selectedUnit(nullptr),
  _battle(nullptr)
{
}

InGameMenu::~InGameMenu() {
}

void InGameMenu::setBattle(Battle *battle) {
  _battle = battle;
}

void InGameMenu::build(e_mode mode)
{
  this->init();

  // show unit section only if we selected a unit
  // here, we cannot use cursor's position, we could have move the unit
  Unit *current_unit = g_status->map()->unit(g_status->selectedCell());
  if (current_unit
      && current_unit->playerId() == g_status->currentPlayer()
      && !current_unit->played())
  {
    if (mode == E_MODE_SELECTION_MENU)
    {
      MenuEntry move("Move", E_ENTRY_MOVE);
      _entries->push_back(move);
    }
    if (mode == E_MODE_ACTION_MENU)
    {
      MenuEntry stop("Stop", E_ENTRY_STOP);
      _entries->push_back(stop);
    }
  }
  else
  {
    // next turn button
    MenuEntry next_turn("Next\n\tTurn", E_ENTRY_NEXT_TURN);
    _entries->push_back(next_turn);
  }

  // target
  if (mode == E_MODE_ACTION_MENU
      && g_status->map()->unit(CURSOR->x(), CURSOR->y()))
  {
    MenuEntry attack("Attack", E_ENTRY_ATTACK);
    _entries->push_back(attack);
  }

  MenuEntry cancel("Cancel", E_ENTRY_CANCEL);
  _entries->push_back(cancel);

  _nbEntries = _entries->size();
  setOrigin();
}


void InGameMenu::executeEntry()
{
  e_mode old_mode = E_MODE_NONE;
  Unit *selectedUnit = nullptr;

  switch ((*_entries)[_selectedEntry].id())
  {
    case E_ENTRY_ATTACK:
      std::cout << "attack" << std::endl;
      break;

    case E_ENTRY_STOP:
      selectedUnit = g_status->map()->unit(_selectedUnitPosition);
      selectedUnit->setLocation(CURSOR->coords());
      if (_selectedUnitPosition != CURSOR->coords())
        g_status->map()->moveUnit();

      g_status->exitToMode(E_MODE_PLAYING, true);
      g_interface->path()->hideAllowedPath();
      break;

    case E_ENTRY_MOVE:
      g_status->pushModeInGameMenu(E_MODE_MOVING_UNIT, this);
      _selectedUnitPosition = CURSOR->coords();
      g_interface->setPathOrigin(_selectedUnitPosition);
      break;

    case E_ENTRY_NEXT_TURN:
      _battle->nextPlayer();
      g_status->exitCurrentMode(true);
      break;

    case E_ENTRY_CANCEL:
      old_mode = CURRENT_MODE;
      this->loadMenu(g_status->popCurrentMode()->menu());

      // if we were dealing with orders, return to the unit position
      if (old_mode == E_MODE_ACTION_MENU && CURRENT_MODE == E_MODE_MOVING_UNIT)
      {
        g_status->exitCurrentMode();
        this->build(CURRENT_MODE); // re-build menu at selection state
      }
      break;

    default:
      Debug::logPrintf("unable to match selection menu entry");
      break;
  }

  _selectedEntry = 0;
}
