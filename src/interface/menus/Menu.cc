#include <interface/menus/Menu.hh>
#include <interface/menus/MenuEntry.hh>
#include <common/constants.hh>
#include <common/macros.hh>
#include <common/Status.hh>
#include <context/State.hh>
#include <input/EventManager.hh>


namespace interface {


Menu::Menu()
  : InterfaceElement("selection_menu_button")
  , _selectedEntry (0)
{
  _entries = std::vector<std::shared_ptr<MenuEntry>> ();
  _origin = {0, 0};
}


Menu::Menu(std::vector<std::shared_ptr<MenuEntry>> &entries)
  : InterfaceElement("selection_menu_button")
  , _selectedEntry (0)
{
  _entries = std::vector<std::shared_ptr<MenuEntry>> (entries);

  // _origin.x = (CURSOR->x() + 1) * CELL_WIDTH + GRID_OFFSET_X;
  // _origin.y = CURSOR->y() * CELL_HEIGHT + GRID_OFFSET_Y;
}


void Menu::setOrigin()
{
//    /// \todo sets the menu at right (cursor-relative) position
//   _origin.x = (CURSOR->x() + 1) * CELL_WIDTH + GRID_OFFSET_X;
//   _origin.y = CURSOR->y() * CELL_HEIGHT + GRID_OFFSET_Y;
}


void Menu::setOrigin(Coords origin)
{
  _origin = origin;
}


void Menu::decrementSelectedEntry()
{
  if (_selectedEntry)
    _selectedEntry = (_selectedEntry - 1) % (_entries.size() - 1);
  else
    _selectedEntry = _entries.size() - 1;
}


void Menu::executeEntry()
{
//  (_entries)[_selectedEntry].execute();
//  _selectedEntry = 0;
}


void Menu::draw()
{
  if (_entries.size() == 0)
  {
    PRINTF("on demand build");
    build(/* Status::currentState() */); // use a cache (when pushing state)
  }

  // setOrigin();
  // Coords v_rect(_origin);
  // for (auto it: _entries)
  // {
  //   it.draw(v_rect);
  //   v_rect -= Coords(0, CELL_HEIGHT);
  // }

  // // showing selection rectangle
  // _imageSelection = GETIMAGE("selection_menu_selection");
  // _imageSelection.setSize(sf::Vector2f(2 * CELL_WIDTH, CELL_HEIGHT));
  // _imageSelection.setPosition(_origin - sf::Vector2f(0, CELL_HEIGHT * _selectedEntry));
  // _imageSelection.draw();
}



} // namespace interface
