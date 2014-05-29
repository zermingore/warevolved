#include <interface/menus/EntriesMenu.hh>
#include <interface/menus/MenuEntry.hh>
#include <common/constants.hh>
#include <common/globals.hh>
#include <common/macros.hh>


EntriesMenu::EntriesMenu() :
  _selectedEntry (0),
  _nbEntries (0),
  _entries (nullptr),
  _imageSelection (nullptr)
{
}


EntriesMenu::EntriesMenu(std::vector<MenuEntry> entries) :
    _selectedEntry (0),
    _imageSelection (nullptr)
{
  _entries = new std::vector<MenuEntry>;
  *_entries = entries;
  _nbEntries = entries.size();

  _origin.x = (CURSOR->getX() + 1) * CELL_WIDTH + GRID_OFFSET_X;
  _origin.y = CURSOR->getY() * CELL_HEIGHT + GRID_OFFSET_Y;
}


EntriesMenu::~EntriesMenu() {
  delete _entries;
}

void EntriesMenu::init()
{
  this->setOrigin();
  _entries = new std::vector<MenuEntry>;
  _entries->clear();
}


unsigned int EntriesMenu::selectedEntry() {
  return _selectedEntry;
}


std::vector<MenuEntry> *EntriesMenu::getEntries() {
  return _entries ? _entries : nullptr;
}

void EntriesMenu::loadMenu(EntriesMenu *menu)
{
  _entries = menu->getEntries();
  _nbEntries = _entries->size();
  _selectedEntry = menu->selectedEntry();
  this->setOrigin();
}


void EntriesMenu::setOrigin()
{
  // TODO sets the menu at right (cursor-relative) position
  _origin.x = (CURSOR->getX() + 1) * CELL_WIDTH + GRID_OFFSET_X;
  _origin.y = CURSOR->getY() * CELL_HEIGHT + GRID_OFFSET_Y;
}

void EntriesMenu::incrementSelectedEntry() {
  ++_selectedEntry %= _nbEntries;
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
    this->build(CURRENT_MODE); // use a cache (when pushing state)
  }

  this->setOrigin();
  sf::Vector2f v_rect(_origin);
  for (MenuEntry it: *_entries)
  {
    it.draw(v_rect);
    v_rect -= sf::Vector2f(0, CELL_HEIGHT);
  }

  // showing selection rectangle
  _imageSelection = GETIMAGE("selection_menu_selection");
  _imageSelection->setSize(sf::Vector2f(2 * CELL_WIDTH, CELL_HEIGHT));
  _imageSelection->setPosition(_origin - sf::Vector2f(0, CELL_HEIGHT * _selectedEntry));
  _imageSelection->draw();
}


void EntriesMenu::resetSelectedEntry() {
  _selectedEntry = 0;
}
