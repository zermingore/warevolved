#include <interface/SelectionMenu.hh>
#include <interface/MenuEntry.hh>
#include <common/globals.hh>


SelectionMenu::SelectionMenu() :
  _selectedEntry (0),
  _nbEntries (1)
{
  _sprite = new sf::Sprite();
}

SelectionMenu::~SelectionMenu()
{
  delete _sprite;

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
  unsigned int curs_x = g_status->getCursor()->getX();
  unsigned int curs_y = g_status->getCursor()->getY();

  _nbEntries = 1;
  //_selectedEntry = 0;

  // TODO sets the menu at right (cursor-relative) position
  sf::Vector2f v_rect((curs_x + 1) * CELL_WIDTH + g_status->getGridOffsetX(),
					  curs_y * CELL_HEIGHT + g_status->getGridOffsetY());

  sf::Vector2f origin_menu(v_rect);

  // show unit section only if we selected a unit
  // TODO check if we can control it
  // here, we cannot use cursor's position, we could have move the unit
  if (g_status->getMap()->getUnit(g_status->getSelectedCell()))
  {
	MenuEntry move("move");
	move.draw(v_rect);
	v_rect -= sf::Vector2f(0, CELL_WIDTH);

	++_nbEntries;
  }

  // next turn button
  MenuEntry move("Next\n\tTurn"); // FIXME hard-coded
  move.draw(v_rect);
  v_rect -= sf::Vector2f(0, CELL_WIDTH);

  // showing selection rectangle
  _imageBackground = GETIMAGE("selection_menu_selection");
  _imageBackground->setSize(sf::Vector2f(2 * CELL_WIDTH, CELL_HEIGHT));
  _sprite = _imageBackground->getSprite();
  //_sprite->setPosition(v_rect);


  //std::cout << _selectedEntry << std::endl;

  _sprite->setPosition(origin_menu - sf::Vector2f(0, CELL_HEIGHT * _selectedEntry));

  // _sprite->setTexture(_spritesInterface[E_INTERFACE_IN_GAME_MENU_SELECTION_MENU_SELECTION]);
  _imageBackground->draw();
}
