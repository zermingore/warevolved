#include <interface/menus/Menu.hh>
#include <interface/menus/MenuEntry.hh>
#include <common/constants.hh>
#include <common/globals.hh>
#include <common/macros.hh>


Menu::Menu() :
  _selectedEntry (0),
  _nbEntries (0)
{
  _entries = std::vector<MenuEntry> ();
}


Menu::Menu(std::vector<MenuEntry> &entries) :
    _selectedEntry (0)
{
  _entries = std::vector<MenuEntry> (entries);
  _nbEntries = entries.size();

  _origin.x = (CURSOR->x() + 1) * CELL_WIDTH + GRID_OFFSET_X;
  _origin.y = CURSOR->y() * CELL_HEIGHT + GRID_OFFSET_Y;
}

void Menu::init()
{
  setOrigin();
  _entries.clear();
}

void Menu::loadMenu()
{
  auto menu = g_status->popCurrentMode().menu();
  _entries = menu->getEntries();
  _nbEntries = _entries.size();
  _selectedEntry = menu->selectedEntry();
  setOrigin();
}

void Menu::setOrigin()
{
  // TODO sets the menu at right (cursor-relative) position
  _origin.x = (CURSOR->x() + 1) * CELL_WIDTH + GRID_OFFSET_X;
  _origin.y = CURSOR->y() * CELL_HEIGHT + GRID_OFFSET_Y;
}

void Menu::decrementSelectedEntry()
{
  if (_selectedEntry)
    _selectedEntry = (_selectedEntry - 1) % (_nbEntries - 1);
  else
    _selectedEntry = _nbEntries - 1;
}


void Menu::draw()
{
  if (_entries.size() == 0)
  {
    PRINTF("on demand build");
    build(CURRENT_MODE); // use a cache (when pushing state)
  }

  setOrigin();
  sf::Vector2f v_rect(_origin);
  for (auto it: _entries)
  {
    it.draw(v_rect);
    v_rect -= sf::Vector2f(0, CELL_HEIGHT);
  }

  // showing selection rectangle
  _imageSelection = GETIMAGE("selection_menu_selection");
  _imageSelection.setSize(sf::Vector2f(2 * CELL_WIDTH, CELL_HEIGHT));
  _imageSelection.setPosition(_origin - sf::Vector2f(0, CELL_HEIGHT * _selectedEntry));
  _imageSelection.draw();
}
