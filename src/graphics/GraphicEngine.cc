#include <common/include.hh>
#include <graphics/GraphicEngine.hh>
#include <common/constants.hh>
#include <common/globals.hh>
#include <common/Status.hh>
#include <common/units.hh>
#include <common/terrains.hh>
#include <game/Map.hh>


std::string g_filenames_terrains[E_TERRAINS_NB_TERRAINS] = {
  "forest"
};

std::string g_filenames_units[E_UNITS_NB_UNITS] = {
  "soldiers"
};

std::string g_filenames_interface[E_INTERFACE_NB_INTERFACE] = {
  "selection_menu_button",
  "selection_menu_selection"
};


GraphicEngine::GraphicEngine() {
}

GraphicEngine::GraphicEngine(sf::RenderWindow* window, Map* map, Status* status) :
  _window (window),
  _map (map),
  _status (status),
  _selectedEntry (1)
{
  // initialize render room
  _renderX = _window->getSize().x;
  _renderY = _window->getSize().y;

  // deducing grid position
  _gridOffsetX = (_renderX - g_cell_size * _map->getNbColumns()) / 2;
  _gridOffsetY = (_renderY - g_cell_size * _map->getNbLines()) / 2;

  _fontArmy.loadFromFile(static_cast<std::string>(FONTS_FOLDER) + "army.ttf");

  this->initSprites();
}

GraphicEngine::~GraphicEngine()
{
  delete[] _spritesTerrains;
  delete[] _spritesUnits;
  delete[] _spritesInterface;

  // delete[] g_filenames_terrains;
  // delete[] g_filenames_units;
  // delete[] g_filenames_interface;
}


void GraphicEngine::initSprites()
{
  for (unsigned int i = 0; i < E_TERRAINS_NB_TERRAINS; ++i)
  {
	_spritesTerrains[i] = new sf::Texture();
	_spritesTerrains[i]->loadFromFile(TERRAINS_FOLDER + g_filenames_terrains[i] + ".png");
  }

  for (unsigned int i = 0; i < E_UNITS_NB_UNITS; ++i)
  {
	_spritesUnits[i] = new sf::Texture();
	_spritesUnits[i]->loadFromFile(UNITS_FOLDER + g_filenames_units[i] + ".png");
  }

  for (unsigned int i = 0; i < E_INTERFACE_NB_INTERFACE; ++i)
  {
	_spritesInterface[i] = new sf::Texture();
	_spritesInterface[i]->loadFromFile(INTERFACE_IN_GAME_MENU_FOLDER + g_filenames_interface[i] + ".png");
  }
}


void GraphicEngine::drawScene()
{
  this->drawMap();

  this->drawPanel();
  this->drawMenuBar();

  this->drawCells();
  this->drawGrid();
  this->drawCursor();

  this->drawSelectionMenu();
}


void GraphicEngine::drawMap() // TODO
{
  return;
}

void GraphicEngine::drawPanel()
{
  if (_status->getPanelPosition() == E_PANEL_DEACTIVATED)
	return;

  // TODO manage removal
  // TODO update render zone size if there's a new panel

  // for now, drawing a line to delimit the panel zone
  sf::Vertex line[2] = {
	sf::Vector2f (0.66f * _window->getSize().x, 0),
	sf::Vector2f (0.66f * _window->getSize().x, _window->getSize().y)
  };
  _window->draw(line, 2, sf::Lines);
}

void GraphicEngine::drawMenuBar()
{
  if (_status->getMenuBarPosition() == E_MENU_BAR_DEACTIVATED)
	return;

  // TODO manage removal
  // TODO update render zone size if there's a new bar

  // for now, drawing a line to delimit the menu zone
  sf::Vertex line[2] = {sf::Vector2f (0, g_cell_size / 2),
						sf::Vector2f (_window->getSize().x, g_cell_size / 2)};
  _window->draw(line, 2, sf::Lines);
}


void GraphicEngine::drawCells()
{
  sf::RectangleShape rectangle;
  rectangle.setSize(sf::Vector2f(g_cell_size, g_cell_size));

  for (unsigned int i = 0; i < _map->getNbColumns(); ++i)
	for (unsigned int j = 0; j < _map->getNbLines(); ++j)
  	{
	  e_terrains terrain = _map->getTerrain(i, j);
	  rectangle.setTexture(_spritesTerrains[terrain]);

  	  rectangle.setPosition(i * g_cell_size + g_grid_thickness + _gridOffsetX,
  							j * g_cell_size + g_grid_thickness + _gridOffsetY);
  	  _window->draw(rectangle);

	  e_units unit  = _map->getUnit(i, j);
	  if (unit != E_UNITS_NONE)
	  {
		rectangle.setTexture(_spritesUnits[unit]);
		_window->draw(rectangle);
	  }
  	}
}

// refreshCell // allow to refresh only needed cells (mouse motion)

void GraphicEngine::drawGrid()
{
  sf::Color grid_color(202, 124, 0);

  sf::RectangleShape rectangle;
  rectangle.setSize(sf::Vector2f(g_cell_size, g_cell_size));
  rectangle.setFillColor(sf::Color::Transparent);
  rectangle.setOutlineColor(grid_color);
  rectangle.setOutlineThickness(5);

  // = scroll ? 0 : g_cell_size / 2;
  _gridOffsetX = 0;
  _gridOffsetY = 0;
  if (1) // !scroll // TODO FIXME split offset bottom, ...
  {
	_gridOffsetX = (_renderX - g_cell_size * _map->getNbColumns()) / 2;
	_gridOffsetY = (_renderY - g_cell_size * _map->getNbLines()) / 2;
  }

  for (unsigned int i = 0; i < _map->getNbColumns(); ++i)
  	for (unsigned int j = 0; j < _map->getNbLines(); ++j)
	{
	  rectangle.setPosition(i * g_cell_size + g_grid_thickness + _gridOffsetX,
							j * g_cell_size + g_grid_thickness + _gridOffsetY);
	  _window->draw(rectangle);
	}
}


void GraphicEngine::drawCursor()
{
  //if (_status->getCursor->getVisible())
  _window->draw(_status->getCursor()->getSprite(_gridOffsetX, _gridOffsetY));
}


void GraphicEngine::drawSelectionMenu()
{
  // draw this menu only if requested
  if (!_status->getSelectionMode())
  {
	_selectedEntry = 0;
	return;
  }

  _nbEntries = 1;

  sf::RectangleShape rectangle;
  rectangle.setSize(sf::Vector2f(2 * g_cell_size, g_cell_size));
  rectangle.setTexture(_spritesInterface[E_INTERFACE_IN_GAME_MENU_SELECTION_MENU_BUTTON]);

  unsigned int curs_x = _status->getCursor()->getX();
  unsigned int curs_y = _status->getCursor()->getY();

  // TODO sets the menu at right (cursor-relative) position
  sf::Vector2f v_rect = sf::Vector2f((curs_x + 1) * g_cell_size + _gridOffsetX,
									 curs_y * g_cell_size + _gridOffsetY);

  sf::Vector2f origin_menu = v_rect;

  // show unit section only if we selected a unit
  // TODO check if we can control it
  // here, we cannot use cursor's position, we could have move the unit
  if (_map->getUnit(_status->getSelectedCell()) != E_UNITS_NONE)
  {
	rectangle.setPosition(v_rect);
	_window->draw(rectangle);
	v_rect -= sf::Vector2f(0, g_cell_size);

	// adding text on the button
	sf::Text label("Move", _fontArmy); // TODO hard-coded
	label.setCharacterSize(g_cell_size / 2);
	label.setPosition(rectangle.getPosition());
	_window->draw(label);

	++_nbEntries;
  }

  // next turn button
  rectangle.setPosition(v_rect);
  _window->draw(rectangle);

  sf::Text label("Next\n\tTurn", _fontArmy); // TODO hard-coded
  label.setCharacterSize(g_cell_size / 2);
  label.setPosition(rectangle.getPosition());
  _window->draw(label);

  // showing selection rectangle
  rectangle.setPosition(origin_menu - sf::Vector2f(0, g_cell_size * _selectedEntry));
  rectangle.setTexture(_spritesInterface[E_INTERFACE_IN_GAME_MENU_SELECTION_MENU_SELECTION]);
  _window->draw(rectangle);
}


void GraphicEngine::incrementSelectedEntry()
{
  _selectedEntry = (_selectedEntry + 1) % _nbEntries;
}

void GraphicEngine::decrementSelectedEntry()
{
  _selectedEntry = (_selectedEntry - 1) % _nbEntries;
}
