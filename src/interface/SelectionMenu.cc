#include <interface/SelectionMenu.hh>
#include <interface/MenuEntry.hh>
#include <common/globals.hh>
#include <common/macros.hh>


SelectionMenu::SelectionMenu() :
  _selectedEntry (0),
  _nbEntries (0),
  _imageSelection (NULL)
{
}

SelectionMenu::~SelectionMenu()
{
# ifdef DEBUG_LEAKS
  std::cout << "Selection Menu Dtor" << std::endl;
# endif
}

void SelectionMenu::incrementSelectedEntry() {
  ++_selectedEntry %= _nbEntries;
}

void SelectionMenu::decrementSelectedEntry()
{
  if (_selectedEntry)
    _selectedEntry = (_selectedEntry - 1) % (_nbEntries - 1);
  else
    _selectedEntry = (_nbEntries - 1);
}


void SelectionMenu::build()
{
  _selectedEntry = 0;
  _entries.clear();

  unsigned int x = g_status->getCursor()->getX();
  unsigned int y = g_status->getCursor()->getY();
  // TODO sets the menu at right (cursor-relative) position
  _origin.x = (x + 1) * CELL_WIDTH + GRID_OFFSET_X;
  _origin.y = y * CELL_HEIGHT + GRID_OFFSET_Y;

  // show unit section only if we selected a unit
  // TODO check if we can control it
  // here, we cannot use cursor's position, we could have move the unit
  if (g_status->getMap()->getUnit(g_status->getSelectedCell()))
  {
	  MenuEntry move("Move", E_ENTRIES_MOVE); // FIXME remove
	  _entries.push_back(move);
  }

  MenuEntry void1("void 1", E_ENTRIES_VOID1); // FIXME hard-coded
  _entries.push_back(void1);

  // next turn button
  MenuEntry next_turn("Next\n\tTurn", E_ENTRIES_NEXT_TURN); // FIXME hard-coded
  _entries.push_back(next_turn);

  MenuEntry void2("void 2", E_ENTRIES_VOID2); // FIXME remove
  _entries.push_back(void2);

  _nbEntries = _entries.size();
}


void SelectionMenu::draw()
{
  sf::Vector2f v_rect(_origin);

  for (auto it = _entries.begin(); it != _entries.end(); ++it)
  {
	  it->draw(v_rect);
	  v_rect -= sf::Vector2f(0, CELL_HEIGHT);
  }

  // showing selection rectangle
  _imageSelection = GETIMAGE("selection_menu_selection");
  _imageSelection->setSize(sf::Vector2f(2 * CELL_WIDTH, CELL_HEIGHT));
  _imageSelection->setPosition(_origin - sf::Vector2f(0, CELL_HEIGHT * _selectedEntry));
  _imageSelection->draw();
}


void SelectionMenu::executeEntry()
{
  switch (_entries[_selectedEntry].getId())
  {
    case E_ENTRIES_MOVE:
      g_status->pushMode(E_MODE_MOVING_UNIT);
      std::cout << "move" << std::endl;
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

  //_entries[_selectedEntry]->execute();
}
