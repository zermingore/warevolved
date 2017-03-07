#include <interface/menus/Menu.hh>
#include <interface/menus/MenuEntry.hh>
#include <common/constants.hh>
#include <common/Status.hh>
#include <context/State.hh>
#include <input/EventManager.hh>
#include <game/applications/Battle.hh>
#include <game/Player.hh>
#include <interface/Cursor.hh>

namespace interface {


Menu::Menu()
  : InterfaceElement("selection_menu_button")
  , _selectedEntry (0)
  , _imageSelection(resources::ResourcesManager::getImage("selection_menu_selection"))
{
  _entries = std::vector<std::shared_ptr<MenuEntry>> ();
}


void Menu::setOrigin(Coords origin) {
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
  Status::player()->cursor()->setCoords(_coords);
}


} // namespace interface
