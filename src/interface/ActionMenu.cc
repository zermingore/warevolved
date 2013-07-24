#include <interface/ActionMenu.hh>
#include <interface/MenuEntry.hh>
#include <common/globals.hh>
#include <common/macros.hh>


ActionMenu::ActionMenu() : EntriesMenu() {
}

ActionMenu::~ActionMenu()
{
# ifdef DEBUG_LEAKS
  std::cout << "ActionMenu Dtor" << std::endl;
# endif
}

void ActionMenu::build()
{
  this->init();

  // show unit section only if we selected a unit
  // TODO check if we can control it
  // here, we cannot use cursor's position, we could have move the unit
  if (g_status->getMap()->getUnit(CURSOR->getX(), CURSOR->getY()))
  {
    MenuEntry move("Attack", E_ENTRIES_MOVE);
    _entries.push_back(move);
  }

  MenuEntry stop("Stop", E_ENTRIES_STOP);
  _entries.push_back(stop);

  MenuEntry stop2("Stop2", E_ENTRIES_VOID2); // FIXME remove
  _entries.push_back(stop2);

  _nbEntries = _entries.size();
}


void ActionMenu::executeEntry()
{
  if (_entries.size() == 0)
    this->build();

  switch (_entries[_selectedEntry].getId())
  {
    case E_ENTRIES_ATTACK:
      std::cout << "attack" << std::endl;
      //_path->setOrigin(CURSOR->getX(), CURSOR->getY());
      this->init();
      break;

    case E_ENTRIES_NEXT_TURN:
      std::cout << "next turn" << std::endl;
      g_status->exitCurrentMode();
      break;

    case E_ENTRIES_VOID2:
      std::cout << "void 1" << std::endl;
      g_status->exitCurrentMode();
      break;

    default:
      std::cerr << "unable to match selection menu entry" << std::endl;
  }
}
