#include <common/include.hh>
#include <graphics/GraphicEngine.hh>
#include <resources/ResourcesManager.hh>
#include <common/constants.hh>
#include <common/globals.hh>
#include <common/Status.hh>
#include <common/units.hh>
#include <common/terrains.hh>
#include <game/Map.hh>
#include <common/types.hh>


const std::string g_terrains_names[E_TERRAINS_NB_TERRAINS] = {
  "forest"
};

const std::string g_units_names[E_UNITS_NB_UNITS] = {
  "soldiers"
};

const std::string g_interface_names[E_INTERFACE_NB_INTERFACE] = {
  "selection_menu_button",
  "selection_menu_selection"
};


GraphicEngine::GraphicEngine()
{
  //_fontArmy.loadFromFile(_rm->getFont["font_army"]);
  _fontArmy.loadFromFile(static_cast<std::string>(FONTS_FOLDER) + "army.ttf");

  g_status->getMap()->init(); // TODO move
  //g_status->getMap()->init(_rm);

  //this->initSprites();
}

GraphicEngine::~GraphicEngine()
{
  // delete[] _spritesTerrains;
  // delete[] _spritesUnits;
  // delete[] _spritesInterface;

  // delete[] g_filenames_terrains;
  // delete[] g_filenames_units;
  // delete[] g_filenames_interface;
}


// void GraphicEngine::initSprites()
// {
  // for (unsigned int i = 0; i < E_TERRAINS_NB_TERRAINS; ++i)
  // {
  // 	_spritesTerrains[i] = new sf::Texture();
  // 	_spritesTerrains[i]->loadFromFile(TERRAINS_FOLDER + g_terrains_names[i] + ".png");
  // }
//}


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

void GraphicEngine::drawMap() // TODO (map background)
{
  return;
}

void GraphicEngine::drawPanel()
{
  if (g_status->getPanelPosition() == E_PANEL_DEACTIVATED)
	return;

  // TODO manage removal
  // TODO update render zone size if there's a new panel

  // for now, drawing a line to delimit the panel zone
  sf::Vertex line[2] = {
	sf::Vector2f (0.66f * g_status->getWindow()->getSize().x, 0),
	sf::Vector2f (0.66f * g_status->getWindow()->getSize().x, g_status->getWindow()->getSize().y)
  };
  g_status->getWindow()->draw(line, 2, sf::Lines);
}

void GraphicEngine::drawMenuBar()
{
  if (g_status->getMenuBarPosition() == E_MENU_BAR_DEACTIVATED)
	return;

  // TODO manage removal
  // TODO update render zone size if there's a new bar

  // for now, drawing a line to delimit the menu zone
  sf::Vertex line[2] = {sf::Vector2f (0, g_status->getCellHeight() / 2),
						sf::Vector2f (g_status->getWindow()->getSize().x, (g_status->getCellWidth() + g_status->getCellHeight()) / 4)};
  g_status->getWindow()->draw(line, 2, sf::Lines);
}


void GraphicEngine::drawCells()
{
  for (unsigned int i = 0; i < g_status->getMap()->getNbColumns(); ++i)
	for (unsigned int j = 0; j < g_status->getMap()->getNbLines(); ++j)
  	{
	  e_terrains terrain = g_status->getMap()->getTerrain(i, j);
	  // _rm->getImage(g_status->getMap()->getTerrainId())->display());
	  // _rm->getImage(E_TYPES_TERRAIN, [g_status->getMap()->getTerrain(i, j)])->draw()

	  //_rm->getImage(g_status->getMap()->getTerrainId())->draw(i, j);

	  e_units unit  = g_status->getMap()->getUnit(i, j);
	  // if (unit != E_UNITS_NONE)
	  // 	_rm->getImage(g_units_names[unit])->draw(i, j);
  	}
}


void GraphicEngine::drawGrid()
{
  sf::Color grid_color(202, 124, 0);

  sf::RectangleShape rectangle;
  rectangle.setSize(sf::Vector2f(g_status->getCellWidth(), g_status->getCellHeight()));
  rectangle.setFillColor(sf::Color::Transparent);
  rectangle.setOutlineColor(grid_color);
  rectangle.setOutlineThickness(5);

  // = scroll ? 0 : (g_status->getCellWidth() + g_status->getCellHeight()) / 4;
  g_status->setGridOffsetX(0);
  g_status->setGridOffsetY(0);
  if (1) // !scroll // TODO FIXME split offset bottom, ...
  {
	g_status->setGridOffsetX((g_status->getRenderX() - g_status->getCellWidth() * g_status->getMap()->getNbColumns()) / 2);
	g_status->setGridOffsetY((g_status->getRenderY() - g_status->getCellHeight() * g_status->getMap()->getNbLines()) / 2);
  }

  for (unsigned int i = 0; i < g_status->getMap()->getNbColumns(); ++i)
  	for (unsigned int j = 0; j < g_status->getMap()->getNbLines(); ++j)
	{
	  rectangle.setPosition(i * g_status->getCellWidth() + g_status->getGridThickness() + g_status->getGridOffsetX(),
							j * g_status->getCellHeight() + g_status->getGridThickness() + g_status->getGridOffsetY());
	  g_status->getWindow()->draw(rectangle);
	}
}


void GraphicEngine::drawCursor()
{
  // if (_status->getCursor->getVisible())
  g_status->getWindow()->draw(g_status->getCursor()->getSprite(g_status->getGridOffsetX(), g_status->getGridOffsetY()));
}


void GraphicEngine::drawSelectionMenu()
{
  // draw this menu only if requested
  if (!g_status->getSelectionMode())
  {
	_selectedEntry = 0;
	return;
  }

  _nbEntries = 1;

  sf::RectangleShape rectangle;
  rectangle.setSize(sf::Vector2f(2 * g_status->getCellWidth(), g_status->getCellHeight()));
  rectangle.setTexture(_spritesInterface[E_INTERFACE_IN_GAME_MENU_SELECTION_MENU_BUTTON]);

  unsigned int curs_x = g_status->getCursor()->getX();
  unsigned int curs_y = g_status->getCursor()->getY();

  // TODO sets the menu at right (cursor-relative) position
  sf::Vector2f v_rect = sf::Vector2f((curs_x + 1) * g_status->getCellWidth() + g_status->getGridOffsetX(),
									 curs_y * g_status->getCellHeight() + g_status->getGridOffsetY());

  sf::Vector2f origin_menu = v_rect;

  // show unit section only if we selected a unit
  // TODO check if we can control it
  // here, we cannot use cursor's position, we could have move the unit
  if (g_status->getMap()->getUnit(g_status->getSelectedCell()) != E_UNITS_NONE)
  {
	rectangle.setPosition(v_rect);
	g_status->getWindow()->draw(rectangle);
	v_rect -= sf::Vector2f(0, g_status->getCellWidth());

	// adding text on the button
	sf::Text label("Move", _fontArmy); // TODO hard-coded
	label.setCharacterSize((g_status->getCellWidth() + g_status->getCellHeight()) / 4);
	label.setPosition(rectangle.getPosition());
	g_status->getWindow()->draw(label);

	++_nbEntries;
  }

  // next turn button
  rectangle.setPosition(v_rect);
  g_status->getWindow()->draw(rectangle);

  sf::Text label("Next\n\tTurn", _fontArmy); // TODO hard-coded
  label.setCharacterSize((g_status->getCellWidth() + g_status->getCellHeight()) / 4);
  label.setPosition(rectangle.getPosition());
  g_status->getWindow()->draw(label);

  // showing selection rectangle
  rectangle.setPosition(origin_menu - sf::Vector2f(0, g_status->getCellWidth() * _selectedEntry));
  rectangle.setTexture(_spritesInterface[E_INTERFACE_IN_GAME_MENU_SELECTION_MENU_SELECTION]);
  g_status->getWindow()->draw(rectangle);
}


void GraphicEngine::incrementSelectedEntry() {
  _selectedEntry = (_selectedEntry + 1) % _nbEntries;
}

void GraphicEngine::decrementSelectedEntry() {
  _selectedEntry = (_selectedEntry - 1) % _nbEntries;
}
