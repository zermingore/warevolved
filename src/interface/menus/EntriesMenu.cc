#include <interface/menus/EntriesMenu.hh>
#include <interface/menus/MenuEntry.hh>
#include <common/constants.hh>
#include <common/globals.hh>
#include <common/macros.hh>


EntriesMenu::EntriesMenu() :
  _selectedEntry (0),
  _nbEntries (0)
{
  _entries = std::make_shared<std::vector<std::shared_ptr<MenuEntry>>> ();
  PRINTF("EntriesMenu Ctor");
}


EntriesMenu::EntriesMenu(std::vector<std::shared_ptr<MenuEntry>> &entries) :
    _selectedEntry (0)
{
  _entries.reset(new std::vector<std::shared_ptr<MenuEntry>> (entries));
  _nbEntries = entries.size();

  _origin.x = (CURSOR->x() + 1) * CELL_WIDTH + GRID_OFFSET_X;
  _origin.y = CURSOR->y() * CELL_HEIGHT + GRID_OFFSET_Y;
}

void EntriesMenu::init()
{
  setOrigin();
  _entries = std::make_shared<std::vector<std::shared_ptr<MenuEntry>>> ();
  _entries->clear();
}

void EntriesMenu::loadMenu()
{
  //_entries.reset(new std::vector<std::shared_ptr<MenuEntry>> (g_status->popCurrentMode().menu()->getEntries()));
  _nbEntries = _entries->size();
  //_selectedEntry = menu.selectedEntry();
  setOrigin();
}

void EntriesMenu::setOrigin()
{
  // TODO sets the menu at right (cursor-relative) position
  _origin.x = (CURSOR->x() + 1) * CELL_WIDTH + GRID_OFFSET_X;
  _origin.y = CURSOR->y() * CELL_HEIGHT + GRID_OFFSET_Y;
}

void EntriesMenu::decrementSelectedEntry()
{
  if (_selectedEntry)
    _selectedEntry = (_selectedEntry - 1) % (_nbEntries - 1);
  else
    _selectedEntry = _nbEntries - 1;
}


void EntriesMenu::draw()
{
  if (_entries->size() == 0)
  {
    DEBUG_PRINT("on demand build");
    build(CURRENT_MODE); // use a cache (when pushing state)
  }

  setOrigin();
  sf::Vector2f v_rect(_origin);
  for (auto it: *_entries)
  {
    it->draw(v_rect);
    v_rect -= sf::Vector2f(0, CELL_HEIGHT);
  }

  // showing selection rectangle
  _imageSelection = GETIMAGE("selection_menu_selection");
  _imageSelection.setSize(sf::Vector2f(2 * CELL_WIDTH, CELL_HEIGHT));
  _imageSelection.setPosition(_origin - sf::Vector2f(0, CELL_HEIGHT * _selectedEntry));
  _imageSelection.draw();
}
