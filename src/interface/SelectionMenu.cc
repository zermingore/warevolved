#include <interface/SelectionMenu.hh>
#include <interface/MenuEntry.hh>
#include <common/globals.hh>
#include <common/macros.hh>


SelectionMenu::SelectionMenu() :
  _x (0),
  _y (0),
  _selectedEntry (0),
  _nbEntries (1)
{
}

SelectionMenu::~SelectionMenu()
{
# ifdef DEBUG_LEAKS
  std::cout << "Selection Menu Dtor" << std::endl;
# endif
}

void SelectionMenu::incrementSelectedEntry() {
  _selectedEntry = (_selectedEntry + 1) % _nbEntries;
}

void SelectionMenu::decrementSelectedEntry() {
  _selectedEntry ? _selectedEntry = (_selectedEntry - 1) % _nbEntries : _selectedEntry = _nbEntries - 1;
}


void SelectionMenu::draw()
{
  _nbEntries = 1;
  unsigned int _x = g_status->getCursor()->getX();
  unsigned int _y = g_status->getCursor()->getY();

  // TODO sets the menu at right (cursor-relative) position
  sf::Vector2f v_rect((_x + 1) * CELL_WIDTH + g_status->getGridOffsetX(),
					  _y * CELL_HEIGHT + g_status->getGridOffsetY());

  sf::Vector2f origin_menu(v_rect);

  // show unit section only if we selected a unit
  // TODO check if we can control it
  // here, we cannot use cursor's position, we could have move the unit
  if (g_status->getMap()->getUnit(g_status->getSelectedCell()))
  {
	MenuEntry move("move"); // FIXME hard-coded
	move.draw(v_rect);
	v_rect -= sf::Vector2f(0, CELL_WIDTH);

	++_nbEntries;
  }

  // next turn button
  MenuEntry move("Next\n\tTurn"); // FIXME hard-coded
  move.draw(v_rect);
  v_rect -= sf::Vector2f(0, CELL_WIDTH);

  // showing selection rectangle
  _imageSelection = GETIMAGE("selection_menu_selection");
  _imageSelection->setSize(sf::Vector2f(2 * CELL_WIDTH, CELL_HEIGHT));
  _selectedEntry = std::min(_selectedEntry, _nbEntries - 1);
  _imageSelection->setPosition(
	origin_menu - sf::Vector2f(0, CELL_HEIGHT * _selectedEntry));
  _imageSelection->draw();
}


void SelectionMenu::executeEntry()
{
  switch (_selectedEntry)
  {
	// case E_MOVE:
	// case E_NEXT_TURN:
	default:
	  std::cerr << "unable to match selection menu entry" << std::endl;
  }
}
