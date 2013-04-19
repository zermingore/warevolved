#include <common/include.hh>
#include <SFML/Graphics/Color.hpp>
#include <core/GraphicEngine.hh>
#include <common/constants.hh>
#include <common/globals.hh>
#include <common/Status.hh>
#include <common/units.hh>
#include <common/terrains.hh>
#include <game/Cursor.hh>
#include <game/Map.hh>

int Status::_panel = 0;
int Status::_menuBar = 0;

std::string g_filenames_terrains[E_NB_TERRAINS] = {
  "forest"
};

std::string g_filenames_units[E_NB_UNITS] = {
  "soldiers"
};


GraphicEngine::GraphicEngine() {
}

GraphicEngine::GraphicEngine(sf::RenderWindow* window, Map* map, Cursor* cursor) :
  _window (window),
  _map (map),
  _cursor (cursor)
{
  // initialize render room
  _renderX = _window->getSize().x;
  _renderY = _window->getSize().y;

  // deducing grid position
  _gridOffsetX = (_renderX - g_cell_size * _map->getNbColumns()) / 2;
  _gridOffsetY = (_renderY - g_cell_size * _map->getNbLines()) / 2;

  this->initSprites();
}

GraphicEngine::~GraphicEngine()
{
  // delete[] _spritesTerrains;
  // delete[] _spritesUnits;
}


void GraphicEngine::initSprites()
{
  for (unsigned int i = 0; i < E_NB_TERRAINS; ++i)
  {
	_spritesTerrains[i] = new sf::Texture();
	_spritesTerrains[i]->loadFromFile(TERRAINS_FOLDER + g_filenames_terrains[i] + ".png");
  }

  for (unsigned int i = 0; i < E_NB_UNITS; ++i)
  {
	_spritesUnits[i] = new sf::Texture();
	_spritesUnits[i]->loadFromFile(UNITS_FOLDER + g_filenames_units[i] + ".png");
  }
}


void GraphicEngine::drawScene()
{
  this->drawMap();

  if (Status::_panel)
  	this->drawPanel();

  if (Status::_menuBar)
  	this->drawMenuBar();

  this->drawCells();
  this->drawGrid();
  this->drawCursor();
}


void GraphicEngine::drawMap() // TODO
{
  return;
}

void GraphicEngine::drawPanel()
{
  // TODO manage removal
  // TODO update render zone size if there's a new panel

  // for mow, drawing a line to delimit the panel zone
  sf::Vertex line[2] = {
	sf::Vector2f (0.66f * _window->getSize().x, 0),
	sf::Vector2f (0.66f * _window->getSize().x, _window->getSize().y)
  };
  _window->draw(line, 2, sf::Lines);
}

void GraphicEngine::drawMenuBar()
{
  // TODO manage removal
  // TODO update render zone size if there's a new bar

  // for mow, drawing a line to delimit the menu zone
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
	  if (unit != E_UNIT_NONE)
	  {
		rectangle.setTexture(_spritesUnits[unit]);
		_window->draw(rectangle);
	  }
  	}
}

// refreshCell // allow to refresh only the needed cell (mouse motion)

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
  // printing Cursor
  _window->draw(_cursor->getSprite(_gridOffsetX, _gridOffsetY));
}


// void GraphicEngine::drawSelectionMenu(Cell* cell)
// {
//   // for (unsigned int i = 0; i < nb_sections; ++i)

//   _window->draw
// }
