#include <common/include.hh>
#include <common/macros.hh>
#include <interface/panels/SidePanel.hh>


SidePanel::SidePanel()
{
  _origin = {0, 0};
  _size = {0, 0};
}

void SidePanel::draw()
{
  // showing selection rectangle
  // _background = GETIMAGE("selection_menu_selection");
  // _background.setSize(sf::Vector2f(2 * CELL_WIDTH, CELL_HEIGHT));
  // _background.setPosition(_origin);
  // _background.draw();

  // for (auto it: _elts)
  //   it.draw();

  // sf::Vertex line[2] = {
  //   sf::Vector2f(_origin.x, _origin.y),
  //   sf::Vector2f(_origin.x, _size.y)
  // };
  // g_window->draw(line, 2, sf::Lines);

  // sf::Vertex line2[2] = {
  //   sf::Vector2f(_origin.x + _size.x, _origin.y),
  //   sf::Vector2f(_origin.x + _size.x, _size.y)
  // };
  // g_window->draw(line2, 2, sf::Lines);

  // auto unit(MAP.unit(CURSOR->coords()));
  // if (unit)
  //   PRINTF(unit->name());
}
