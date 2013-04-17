#include <common/include.hh>
#include <SFML/Graphics/Color.hpp>
#include <core/GraphicEngine.hh>
#include <common/globals.hh>
#include <common/Status.hh>
#include <tools/Cursor.hh>


GraphicEngine::GraphicEngine()
{
}

GraphicEngine::GraphicEngine(sf::RenderWindow* window, Cursor* cursor)
{
  _window = window;
  _cursor = cursor;
}

GraphicEngine::~GraphicEngine()
{
}

int Status::_panel = 0;
int Status::_menuBar = 0;


void GraphicEngine::drawScene()
{
  // initialize render room, update it if there's a new panel, ...
  _renderX = _window->getSize().x;
  _renderY = _window->getSize().y;

  this->drawMap();

  if (Status::_panel)
  	this->drawPanel();

  if (Status::_menuBar)
  	this->drawMenuBar();

  this->drawCells();
  this->drawGrid();
  this->drawCursor();
}


void GraphicEngine::drawMap()
{
  return;
}

void GraphicEngine::drawPanel()
{
  // for mow, drawing a line to delimit the panel zone
  sf::Vertex line[2] = {
	sf::Vector2f (0.66f * _window->getSize().x, 0),
	sf::Vector2f (0.66f * _window->getSize().x, _window->getSize().y)
  };
  _window->draw(line, 2, sf::Lines);

  return;
}

void GraphicEngine::drawMenuBar()
{
  // manage removal

  // for mow, drawing a line to delimit the menu zone
  sf::Vertex line[2] = {sf::Vector2f (0, g_cell_size / 2),
						sf::Vector2f (_window->getSize().x, g_cell_size / 2)};
  _window->draw(line, 2, sf::Lines);

  return;
}

void GraphicEngine::drawCells()
{
  return;
}

// refreshCell // allow to refresh only the needed cell (mouse motion)

void GraphicEngine::drawGrid()
{
  this->drawGrid(5, 5);
  return;
}

void GraphicEngine::drawGrid(unsigned int nb_line, unsigned int nb_column)
{
  sf::Color grid_color(202, 124, 0);

  sf::RectangleShape rectangle;
  rectangle.setSize(sf::Vector2f(g_cell_size, g_cell_size));
  rectangle.setOutlineColor(grid_color);
  rectangle.setOutlineThickness(5);

  // = scroll ? 0 : g_cell_size / 2;
  _gridOffsetX = 0;
  _gridOffsetY = 0;
  if (1) // !scroll // split offset bottom, ...
  {
	_gridOffsetX = (_renderX - g_cell_size * nb_column) / 2;
	_gridOffsetY = (_renderY - g_cell_size * nb_line) / 2;
  }

  for (unsigned int i = 0; i < nb_line; ++i)
  	for (unsigned int j = 0; j < nb_column; ++j)
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
