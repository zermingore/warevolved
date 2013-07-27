#include <interface/Interface.hh>
#include <common/globals.hh>

Interface::Interface()
{
  _cursor = new Cursor();
  _path = new PathFinding();
  _inGameMenu = new InGameMenu();

  g_status->setCursor(_cursor);
}

Interface::~Interface() {
  delete _inGameMenu;
  delete _path;
  delete _cursor;
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
  // if (_cursor->getVisible())
  _cursor->getSprite(GRID_OFFSET_X, GRID_OFFSET_Y);
  _cursor->draw();

  if (CURRENT_MODE == E_MODE_MOVING_UNIT || CURRENT_MODE == E_MODE_ACTION_MENU)
    _path->drawPath();

  if (CURRENT_MODE == E_MODE_SELECTION_MENU || CURRENT_MODE == E_MODE_ACTION_MENU)
    _inGameMenu->draw();
 }
