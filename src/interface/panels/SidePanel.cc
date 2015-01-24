#include <common/include.hh>
#include <common/globals.hh>
#include <common/macros.hh>
#include <interface/panels/SidePanel.hh>
#include <interface/panels/SidePanel.hxx>

SidePanel::SidePanel() :
  _position (Panel_position::DEACTIVATED)
{
}

void SidePanel::draw()
{
  // showing selection rectangle
  _background = GETIMAGE("panel_background");
  _background.setSize(_size);
  _background.setPosition(_origin);
  _background.draw();

  for (auto it: _elts)
    it.draw();

  sf::Vertex line[2] = {
    sf::Vector2f(_origin.x, _origin.y),
    sf::Vector2f(_origin.x, _size.y)
  };
  g_window->draw(line, 2, sf::Lines);

  sf::Vertex line2[2] = {
    sf::Vector2f(_origin.x + _size.x, _origin.y),
    sf::Vector2f(_origin.x + _size.x, _size.y)
  };
  g_window->draw(line2, 2, sf::Lines);

  auto unit(MAP.unit(CURSOR->coords()));
  if (unit)
    PRINTF(unit->name());
}



Panel_position SidePanel::incrementPosition()
{
  Panel_position old = _position;
  _position++;

  return old;
}
