#include <interface/Interface.hh>


Interface::Interface()
{
  _selectionMenu = new SelectionMenu();
}

Interface::~Interface() {
  delete _selectionMenu;
}

SelectionMenu *Interface::getSelectionMenu() {
  return _selectionMenu;
}
