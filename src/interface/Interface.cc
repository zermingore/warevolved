#include <interface/Interface.hh>
#include <common/globals.hh>

Interface::Interface()
{
  _path = new PathFinding();
  _inGameMenu = new InGameMenu();
}

Interface::~Interface() {
  delete _inGameMenu;
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

void Interface::draw()
{
  if (CURRENT_MODE == E_MODE_MOVING_UNIT || CURRENT_MODE == E_MODE_ACTION_MENU)
    _path->drawPath();

  if (CURRENT_MODE == E_MODE_SELECTION_MENU || CURRENT_MODE == E_MODE_ACTION_MENU)
    _inGameMenu->draw();
 }
