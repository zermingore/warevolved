#include <common/Status.hh>
#include <common/include.hh>


Status::Status() {
  std::cout << "Should *NOT* use this default Constructor for now" << std::endl;
}

Status::Status(Map* map) :
  _map (map),
  _panelPosition (E_PANEL_DEACTIVATED),
  _menuBarPosition (E_MENU_BAR_DEACTIVATED),
  _eventMode (E_EVENT_IN_GAME), // TODO
  _selectionMode (false)
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

bool Status::getSelectionMode() {
  return _selectionMode;
}

e_event_mode Status::getEventMode() {
  return _eventMode;
}

sf::Vector2f Status::getSelectedCell() {
  return _selectedCell;
}

void Status::setSelectionMode(bool selection_mode) {
  _selectionMode = selection_mode;
}

void Status::cellSelection()
{
  if (!_selectionMode)
  {
	_selectedCell.x = _cursor->getX();
	_selectedCell.y = _cursor->getY();
  }

  // updating selection state
  _selectionMode = !_selectionMode;
}
