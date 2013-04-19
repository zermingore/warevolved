#include <common/Status.hh>
#include <common/include.hh>


Status::Status() {
  std::cout << "Should *NOT* use this default Constructor for now" << std::endl;
}

Status::Status(Map* map) :
  _map (map),
  _panelPosition (E_PANEL_DEACTIVATED),
  _menuBarPosition (E_MENU_BAR_DEACTIVATED)
{
  _cursor = new Cursor(_map->getNbColumns(), _map->getNbLines());
}

Status::~Status() {
  delete _cursor;
}

Cursor* Status::getCursor() {
  return _cursor;
}


e_panel_position Status::getPanelPosition() {
  return _panelPosition;
}

e_menu_bar_position Status::getMenuBarPosition() {
  return _menuBarPosition;
}


bool Status::getSelectionActive() {
  return _selectionActive;
}


void Status::cellSelection()
{
  if (!_selectionActive)
  {
	_selectedCell.x = _cursor->getX();
	_selectedCell.y = _cursor->getY();
  }

  // updating selection state
  _selectionActive = !_selectionActive;
}
