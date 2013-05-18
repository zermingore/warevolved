#include <graphics/SelectionMenu.hh>
#include <common/globals.hh>

// scale / size trouble ?

SelectionMenu::SelectionMenu() :
  _nbEntries (1)
{
  _imageBackground = GETIMAGE("selection_menu_button");
  _imageBackground->setSize(sf::Vector2f(2 * g_status->getCellWidth(), g_status->getCellHeight()));
  _sprite = _imageBackground->getSprite();

  // label initialization
  // TODO better calculus, ratio dependent, eventually, text length dependent
  _label = new sf::Text();
  _label->setCharacterSize((CELL_WIDTH + CELL_HEIGHT) / 4);

  //_fontArmy.loadFromFile(_rm->getFont["font_army"]);
  _fontArmy.loadFromFile("resources/fonts/army.ttf");
  _label->setFont(_fontArmy);
}

SelectionMenu::~SelectionMenu() {
  delete _label;
}

void SelectionMenu::incrementSelectedEntry() {
  _selectedEntry = (_selectedEntry + 1) % _nbEntries;
}

void SelectionMenu::decrementSelectedEntry() {
  _selectedEntry = (_selectedEntry - 1) % _nbEntries;
}


void SelectionMenu::draw()
{
  unsigned int curs_x = g_status->getCursor()->getX();
  unsigned int curs_y = g_status->getCursor()->getY();

  // TODO sets the menu at right (cursor-relative) position
  sf::Vector2f v_rect = sf::Vector2f((curs_x + 1) * CELL_WIDTH + g_status->getGridOffsetX(),
									 curs_y * CELL_HEIGHT + g_status->getGridOffsetY());

  sf::Vector2f origin_menu = v_rect;

  // show unit section only if we selected a unit
  // TODO check if we can control it
  // here, we cannot use cursor's position, we could have move the unit
  if (g_status->getMap()->getUnit(g_status->getSelectedCell()) != E_UNITS_NONE)
  {
	_sprite->setPosition(v_rect);
	_imageBackground->draw();
	v_rect -= sf::Vector2f(0, CELL_WIDTH);

	// adding text on the button
	//sf::Text label("Move", _fontArmy); // TODO hard-coded
	_label->setString("Move");
	_label->setPosition(_sprite->getPosition());
	g_status->getWindow()->draw(*_label);

	++_nbEntries;
  }

  // next turn button
  _sprite->setPosition(v_rect);
  _imageBackground->draw();

  //sf::Text label("Next\n\tTurn", _fontArmy); // TODO hard-coded
  _label->setString("Next\n\tTurn");
  _label->setPosition(_sprite->getPosition());
  g_status->getWindow()->draw(*_label);

  // showing selection rectangle
  _sprite->setPosition(origin_menu - sf::Vector2f(0, CELL_HEIGHT * _selectedEntry));
  //_sprite->setTexture(_spritesInterface[E_INTERFACE_IN_GAME_MENU_SELECTION_MENU_SELECTION]);
  _imageBackground->draw();
}
