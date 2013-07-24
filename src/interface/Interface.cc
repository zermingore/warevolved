#include <interface/Interface.hh>


Interface::Interface()
{
  _selectionMenu = new SelectionMenu();
  _actionMenu = new ActionMenu();
}

Interface::~Interface() {
  delete _selectionMenu;
}

SelectionMenu *Interface::getSelectionMenu() {
  return _selectionMenu;
}

ActionMenu *Interface::getActionMenu() {
  return _actionMenu;
}
