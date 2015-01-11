#include <common/include.hh>
#include <common/globals.hh>
#include <common/macros.hh>
#include <interface/panels/Panel.hh>


Panel::Panel()
{
}

void Panel::setOrigin()
{
  // TODO sets the menu at proper position
  _origin.x = 0;
  _origin.y = 0;
}

void Panel::draw()
{
  setOrigin();
  for (auto it: _elts)
    it.draw();

  // showing selection rectangle
  _background = GETIMAGE("selection_menu_selection");
  _background.setSize(sf::Vector2f(2 * CELL_WIDTH, CELL_HEIGHT));
  _background.setPosition(_origin);
  _background.draw();


  // _imageSelection = GETIMAGE("selection_menu_selection");
  // _imageSelection.setSize(sf::Vector2f(2 * CELL_WIDTH, CELL_HEIGHT));
  // _imageSelection.setPosition(_origin - sf::Vector2f(0, CELL_HEIGHT * _selectedEntry));
  // _imageSelection.draw();
}
