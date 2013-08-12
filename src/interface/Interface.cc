#include <interface/Interface.hh>
#include <common/globals.hh>


Interface::Interface() :
  _panelPosition (E_PANEL_DEACTIVATED),
  _menuBarPosition (E_MENU_BAR_DEACTIVATED),
  _modificationPanel (true),
  _modificationMenuBar (true),
  _drawPanel (true),
  _drawMenuBar (true),
  _panelX (0),
  _menuBarY (0)
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

void Interface::incrementPanelPosition()
{
  _panelPosition = static_cast<e_panel_position> ((_panelPosition + 1) % E_PANEL_NB_POSITIONS);
  _modificationPanel = true;
}

void Interface::incrementMenuBarPosition()
{
  _menuBarPosition = static_cast<e_menu_bar_position> ((_menuBarPosition + 1) % E_MENU_BAR_NB_POSITIONS);
  _modificationMenuBar = true;
}


void Interface::setPanel()
{
  if (_panelPosition == E_PANEL_DEACTIVATED)
  {
    g_status->setRenderX(WINDOW_SIZE_X);
    g_status->setGridOffsetX((WINDOW_SIZE_X - CELL_WIDTH * NB_COLUMNS) / 2);
    _modificationPanel = false;

    return;
  }

  unsigned int offset = 4 * CELL_WIDTH;
  unsigned int render_x = WINDOW_SIZE_X - offset;
  g_status->setRenderX(render_x);
  if (_panelPosition == E_PANEL_LEFT)
  {
    g_status->setGridOffsetX(offset + GRID_THICKNESS);
    _panelX = WINDOW_SIZE_X - render_x - (render_x - CELL_WIDTH * NB_COLUMNS) / 2;
  }
  else
  {
    g_status->setGridOffsetX((render_x - CELL_WIDTH * NB_COLUMNS) / 2 - GRID_THICKNESS);
    _panelX = render_x;
  }

  _modificationPanel = false;
}


void Interface::setMenuBar()
{
  if (_menuBarPosition == E_MENU_BAR_DEACTIVATED)
  {
    g_status->setRenderY(WINDOW_SIZE_Y);
    g_status->setGridOffsetY((WINDOW_SIZE_Y - CELL_HEIGHT * NB_LINES) / 2);
    _modificationMenuBar = false;

    return;
  }

  unsigned int render_y = WINDOW_SIZE_Y - CELL_HEIGHT / 2;
  g_status->setRenderY(WINDOW_SIZE_Y - render_y);

  unsigned int offset = (render_y - CELL_HEIGHT * NB_LINES) / 2;
  if (_menuBarPosition == E_MENU_BAR_TOP)
  {
    g_status->setGridOffsetY(offset + CELL_HEIGHT / 2 - GRID_THICKNESS);
    _menuBarY = CELL_HEIGHT / 2;
  }
  else
  {
    g_status->setGridOffsetY(offset - GRID_THICKNESS);
    _menuBarY = WINDOW_SIZE_Y - CELL_HEIGHT / 2;
  }

  _modificationMenuBar = false;
}


void Interface::drawPanel()
{
  if (_panelPosition == E_PANEL_DEACTIVATED)
    return;

  sf::Vertex line[2] = {
      sf::Vector2f (_panelX, 0),
      sf::Vector2f (_panelX, WINDOW_SIZE_Y)
  };
  WINDOW->draw(line, 2, sf::Lines);

  Unit *unit = g_status->getMap()->getUnit(CURSOR->getCoords());
  if (unit)
    DEBUG_PRINT(unit->getName());
}


void Interface::drawMenuBar()
{
  if (_menuBarPosition == E_MENU_BAR_DEACTIVATED)
    return;

  sf::Vertex line[2] = {
      sf::Vector2f (0, _menuBarY),
      sf::Vector2f (WINDOW_SIZE_X, _menuBarY)
  };
  WINDOW->draw(line, 2, sf::Lines);
}


void Interface::draw()
{
  if (_modificationPanel)
    this->setPanel();

  if (_modificationMenuBar)
    this->setMenuBar();

  // if (_cursor->getVisible())
  _cursor->getSprite(GRID_OFFSET_X, GRID_OFFSET_Y);
  _cursor->draw();

  this->drawPanel();
  this->drawMenuBar();

  if (CURRENT_MODE == E_MODE_MOVING_UNIT || CURRENT_MODE == E_MODE_ACTION_MENU)
    _path->drawPath();

  if (CURRENT_MODE == E_MODE_SELECTION_MENU || CURRENT_MODE == E_MODE_ACTION_MENU)
    _inGameMenu->draw();
}
