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
    MenuEntry attack("Attack", E_ENTRIES_ATTACK);
    _entries.push_back(attack);
  }

  MenuEntry stop("Stop", E_ENTRIES_STOP);
  _entries.push_back(stop);

  _nbEntries = _entries.size();
}


void ActionMenu::executeEntry()
{
  if (_entries.size() == 0)
  {
    this->build();
    DEBUG_PRINT("invalid exec request");
  }

  switch (_entries[_selectedEntry].getId())
  {
    case E_ENTRIES_ATTACK:
      std::cout << "attack" << std::endl;
      break;

    case E_ENTRIES_STOP:
      std::cout << "stop" << std::endl;
      break;

    default:
      std::cerr << "unable to match selection menu entry" << std::endl;
  }

//  g_status->exitCurrentMode();
}
