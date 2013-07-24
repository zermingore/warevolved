#include <interface/SelectionMenu.hh>
#include <interface/MenuEntry.hh>
#include <common/globals.hh>
#include <common/macros.hh>


SelectionMenu::SelectionMenu() : EntriesMenu() {
}

SelectionMenu::~SelectionMenu()
{
# ifdef DEBUG_LEAKS
  std::cout << "Selection Menu Dtor" << std::endl;
# endif
}

void SelectionMenu::build()
{
  this->init();

  // show unit section only if we selected a unit
  // TODO check if we can control it
  // here, we cannot use cursor's position, we could have move the unit
  if (g_status->getMap()->getUnit(g_status->getSelectedCell()))
  {
    MenuEntry move("Move", E_ENTRIES_MOVE);
    _entries.push_back(move);
  }
  else
  {
    // next turn button
    MenuEntry next_turn("Next\n\tTurn", E_ENTRIES_NEXT_TURN);
    _entries.push_back(next_turn);
  }

  MenuEntry void1("void 1", E_ENTRIES_VOID1); // FIXME remove
  _entries.push_back(void1);

  MenuEntry void2("void 2", E_ENTRIES_VOID2); // FIXME remove
  _entries.push_back(void2);

  _nbEntries = _entries.size();
}


void SelectionMenu::executeEntry()
{
  switch (_entries[_selectedEntry].getId())
  {
    case E_ENTRIES_MOVE:
      g_status->pushMode(E_MODE_MOVING_UNIT);
      std::cout << "move" << std::endl;
      _path->setOrigin(CURSOR->getX(), CURSOR->getY());
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
  }
}
