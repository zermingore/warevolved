#include <interface/menus/InGameMenu.hh>
#include <interface/menus/MenuEntry.hh>
#include <common/globals.hh>
#include <common/macros.hh>


InGameMenu::InGameMenu() : EntriesMenu() {
}

InGameMenu::~InGameMenu()
{
# ifdef DEBUG_LEAKS
  std::cout << "InGameMenu Dtor" << std::endl;
# endif
}

void InGameMenu::build()
{
  this->init();

  // show unit section only if we selected a unit
  // TODO check if we can control it
  // here, we cannot use cursor's position, we could have move the unit
  if (g_status->getMap()->getUnit(g_status->getSelectedCell()))
  {
    if (CURRENT_MODE == E_MODE_PLAYING || CURRENT_MODE == E_MODE_SELECTION_MENU)
    {
      MenuEntry move("Move", E_ENTRIES_MOVE);
      _entries.push_back(move);
    }
    if (CURRENT_MODE == E_MODE_ACTION_MENU)
    {
      MenuEntry stop("Stop", E_ENTRIES_STOP);
      _entries.push_back(stop);
    }
  }
  else
  {
    // next turn button
    MenuEntry next_turn("Next\n\tTurn", E_ENTRIES_NEXT_TURN);
    _entries.push_back(next_turn);
  }

  // target
  if (CURRENT_MODE == E_MODE_ACTION_MENU &&
      g_status->getMap()->getUnit(CURSOR->getX(), CURSOR->getY()))
  {
    MenuEntry attack("Attack", E_ENTRIES_ATTACK);
    _entries.push_back(attack);
  }

  _nbEntries = _entries.size();
  this->setOrigin();
}


void InGameMenu::executeEntry()
{
  if (_entries.size() == 0)
  {
    this->build();
    DEBUG_PRINT("invalid execution request, rebuilding...");
  }

  switch (_entries[_selectedEntry].getId())
  {
    case E_ENTRIES_ATTACK:
      std::cout << "attack" << std::endl;
      break;

    case E_ENTRIES_STOP:
      std::cout << "stop" << std::endl;
      break;

    case E_ENTRIES_MOVE:
      g_status->pushMode(E_MODE_MOVING_UNIT);
      std::cout << "move" << std::endl;
      g_interface->setPathOrigin(CURSOR->getCoords());
      break;

    case E_ENTRIES_NEXT_TURN:
      std::cout << "next turn" << std::endl;
      g_status->exitCurrentMode();
      break;

    case E_ENTRIES_VOID1:
      std::cout << "void 1" << std::endl;
      g_status->exitCurrentMode();
      break;

    case E_ENTRIES_VOID2:
      std::cout << "void 2" << std::endl;
      g_status->exitCurrentMode();
      break;

    default:
      std::cerr << "unable to match selection menu entry" << std::endl;
      break;
  }
}
