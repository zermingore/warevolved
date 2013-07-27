#include <interface/Interface.hh>
#include <common/globals.hh>


Interface::Interface() :
  _panelPosition (E_PANEL_DEACTIVATED),
  _menuBarPosition (E_MENU_BAR_DEACTIVATED)
{
  _cursor = new Cursor();
  _path = new PathFinding();
  _inGameMenu = new InGameMenu();
}

Interface::~Interface() {
  delete _inGameMenu;
  delete _path;
  delete _cursor;
}

Cursor *Interface::getCursor() {
  return _cursor;
}

e_panel_position Interface::getPanelPosition() {
  return _panelPosition;
}

e_menu_bar_position Interface::getMenuBarPosition() {
  return _menuBarPosition;
}

InGameMenu *Interface::getInGameMenu() {
  return _inGameMenu;
}

PathFinding *Interface::getPath() {
  return _path;
}

void Interface::setPathOrigin(Coords coords) {
  _path->setOrigin(coords);
}

void Interface::incrementPanelPosition() {
  _panelPosition = static_cast<e_panel_position> ((_panelPosition + 1) % E_PANEL_NB_POSITIONS);
}

void Interface::draw()
{
  // if (_cursor->getVisible())
  _cursor->getSprite(GRID_OFFSET_X, GRID_OFFSET_Y);
  _cursor->draw();

  if (CURRENT_MODE == E_MODE_MOVING_UNIT || CURRENT_MODE == E_MODE_ACTION_MENU)
    _path->drawPath();

  if (CURRENT_MODE == E_MODE_SELECTION_MENU || CURRENT_MODE == E_MODE_ACTION_MENU)
    _inGameMenu->draw();
 }
