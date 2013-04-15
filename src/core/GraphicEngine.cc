#include <common/include.hh>
#include <SFML/Graphics/Color.hpp>
#include <core/GraphicEngine.hh>
#include <common/globals.hh>
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

// drawMap
// refreshCell // allow to refresh only the needed cell (mouse motion)

void GraphicEngine::drawGrid()
{
}

void GraphicEngine::drawGrid(unsigned int nb_line, unsigned int nb_column)
{
  if (_window->getSize().x / nb_line < g_cell_size) // NOTICE: pop 1 time at closure
	std::cerr << "limit exceeded: " << _window->getSize().x << std::endl; // TODO add a scroll


  // Lines Method
  // sf::Vertex line[2] = {sf::Vector2f (0,0), sf::Vector2f (700,500)};
  // _window->draw(line, 2, sf::Lines);


  sf::Color grid_color(202, 124, 0);

  sf::RectangleShape rectangle;
  rectangle.setSize(sf::Vector2f(g_cell_size, g_cell_size));
  rectangle.setOutlineColor(grid_color);
  rectangle.setOutlineThickness(5);

  int offset = 0; // = scroll ? 0 : g_cell_size / 2;
  if (1) // !scroll
  {
	offset = g_cell_size / 2;
  }

  for (unsigned int i = 0; i < nb_line; ++i)
  	for (unsigned int j = 0; j < nb_column; ++j)
	{
	  rectangle.setPosition(i * g_cell_size + g_grid_thickness + offset,
							j * g_cell_size + g_grid_thickness + offset);
	  _window->draw(rectangle);
	}

  // printing Cursor
  _window->draw(_cursor->getSprite());
}
