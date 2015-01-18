#include <interface/panels/MenuBar.hh>
#include <common/include.hh>
#include <common/globals.hh>
#include <common/macros.hh>


void MenuBar::draw()
{
  // showing selection rectangle
  _background = GETIMAGE("selection_menu_selection");
  _background.setSize(sf::Vector2f(2 * CELL_WIDTH, CELL_HEIGHT));
  _background.setPosition(_origin);
  _background.draw();

  for (auto it: _elts)
    it.draw();

  sf::Vertex line[2] = {
    sf::Vector2f(_origin.x, _origin.y + _size.y),
    sf::Vector2f(_size.x, _origin.y + _size.y)
  };
  g_window->draw(line, 2, sf::Lines);
  sf::Vertex line2[2] = {
    sf::Vector2f(_origin.x, _origin.y),
    sf::Vector2f(_size.x, _origin.y)
  };
  g_window->draw(line2, 2, sf::Lines);
}
