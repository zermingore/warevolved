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
  // TODO check if we can control it
  // here, we cannot use cursor's position, we could have move the unit
  Unit *current_unit = g_status->getMap()->getUnit(g_status->getSelectedCell());
  if (current_unit && current_unit->getPlayerId() == g_status->getCurrentPlayer())
  {
    if (mode == E_MODE_SELECTION_MENU) //  || mode == E_MODE_MOVING_UNIT
    {
      MenuEntry move("Move", E_ENTRIES_MOVE);
      _entries->push_back(move);
    }
    if (mode == E_MODE_ACTION_MENU)
    {
      MenuEntry stop("Stop", E_ENTRIES_STOP);
      _entries->push_back(stop);
    }
  }
  else
  {
    // next turn button
    MenuEntry next_turn("Next\n\tTurn", E_ENTRIES_NEXT_TURN);
    _entries->push_back(next_turn);

    MenuEntry void1("void1", E_ENTRIES_VOID1);
    _entries->push_back(void1);
    MenuEntry void2("void2", E_ENTRIES_VOID2);
    _entries->push_back(void2);
  }

  // target
  if (mode == E_MODE_ACTION_MENU &&
      g_status->getMap()->getUnit(CURSOR->getX(), CURSOR->getY()))
  {
    MenuEntry attack("Attack", E_ENTRIES_ATTACK);
    _entries->push_back(attack);
  }

  MenuEntry cancel("Cancel", E_ENTRIES_CANCEL);
  _entries->push_back(cancel);

  _nbEntries = _entries->size();
  this->setOrigin();
}


void InGameMenu::executeEntry()
{
  e_mode old_mode = E_MODE_NONE;
  Unit *selectedUnit = nullptr;

  switch ((*_entries)[_selectedEntry].getId())
  {
    case E_ENTRIES_ATTACK:
      std::cout << "attack" << std::endl;
      break;

    case E_ENTRIES_STOP:
      selectedUnit = g_status->getMap()->getUnit(_selectedUnitPosition);
      selectedUnit->setLocation(CURSOR->getCoords());
      if (_selectedUnitPosition != CURSOR->getCoords())
        g_status->getMap()->moveUnit();
      g_status->exitToMode(E_MODE_PLAYING, true);
      break;

    case E_ENTRIES_MOVE:
      g_status->pushModeInGameMenu(E_MODE_MOVING_UNIT, this);
      _selectedUnitPosition = CURSOR->getCoords();
      g_interface->setPathOrigin(_selectedUnitPosition);
      break;

    case E_ENTRIES_NEXT_TURN:
      _battle->nextPlayer();
      g_status->exitCurrentMode(true);
      // reset _played in player unit list
      break;

    case E_ENTRIES_VOID1:
      std::cout << "void 1" << std::endl;
      g_status->exitCurrentMode();
      break;

    case E_ENTRIES_VOID2:
      std::cout << "void 2" << std::endl;
      g_status->exitCurrentMode();
      break;

    case E_ENTRIES_CANCEL:
      old_mode = CURRENT_MODE;
      this->loadMenu(g_status->popCurrentMode()->getMenu());

      // if we were dealing with orders, return to the unit position
      if (old_mode == E_MODE_ACTION_MENU && CURRENT_MODE == E_MODE_MOVING_UNIT)
      {
        g_status->exitCurrentMode();
        this->build(CURRENT_MODE); // re-build menu at selection state
      }

      DEBUG_PRINT("cancel");
      break;

    default:
      std::cerr << "unable to match selection menu entry" << std::endl;
      break;
  }

  _selectedEntry = 0;
}
