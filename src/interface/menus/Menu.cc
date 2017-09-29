#include <interface/menus/Menu.hh>

#include <debug/Debug.hh>
#include <interface/menus/MenuEntry.hh>
#include <game/Status.hh>
#include <context/State.hh>
#include <input/EventManager.hh>
#include <game/Battle.hh>
#include <game/Player.hh>
#include <interface/Cursor.hh>

namespace interface {


Menu::Menu()
  : InterfaceElement("selection_menu_button")
  , _selectedEntry (0)
  , _imageSelection(resources::ResourcesManager::getSprite("selection_menu_selection"))
{
}


void Menu::setOrigin(const Coords origin)
{
  /// \todo set the menu at optimal coordinates
  _origin = origin;
}


void Menu::decrementSelectedEntry()
{
  if (_selectedEntry) {
    _selectedEntry = (_selectedEntry - 1) % (_entries.size() - 1);
  }
  else {
    _selectedEntry = _entries.size() - 1;
  }
}


void Menu::draw()
{
  if (_entries.size() == 0)
  {
    PRINTF("on demand build");
    build(); // use a cache (when pushing state)
  }
}


void Menu::resume() {
  game::Status::player()->cursor()->setCoords(_coords);
}


} // namespace interface
