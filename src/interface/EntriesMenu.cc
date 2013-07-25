#include <interface/EntriesMenu.hh>
#include <interface/MenuEntry.hh>
#include <common/constants.hh>
#include <common/globals.hh>
#include <common/macros.hh>


EntriesMenu::EntriesMenu() :
  _selectedEntry (0),
  _nbEntries (0),
  _imageSelection (NULL),
  _path (NULL)
{
}

EntriesMenu::~EntriesMenu()
{
# ifdef DEBUG_LEAKS
  std::cout << "Entries Menu Dtor" << std::endl;
# endif
}

void EntriesMenu::init()
{
  this->setOrigin();
  _selectedEntry = 0;
  _entries.clear();
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
    _selectedEntry = (_nbEntries - 1);
}

void EntriesMenu::setPath(PathFinding *path) {
  _path = path;
}


void EntriesMenu::draw()
{
  if (abs(_origin.x) < EPSILON && abs(_origin.y) < EPSILON)
    this->build();

  this->setOrigin();
  sf::Vector2f v_rect(_origin);
  for (auto it = _entries.begin(); it != _entries.end(); ++it)
  {
    it->draw(v_rect);
    v_rect -= sf::Vector2f(0, CELL_HEIGHT);
  }

  // showing selection rectangle
  _imageSelection = GETIMAGE("selection_menu_selection");
  _imageSelection->setSize(sf::Vector2f(2 * CELL_WIDTH, CELL_HEIGHT));
  _imageSelection->setPosition(_origin - sf::Vector2f(0, CELL_HEIGHT * _selectedEntry));
  _imageSelection->draw();
}
