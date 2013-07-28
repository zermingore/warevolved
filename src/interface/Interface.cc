#include <interface/Interface.hh>
#include <common/globals.hh>


Interface::Interface() :
  _panelPosition (E_PANEL_DEACTIVATED),
  _menuBarPosition (E_MENU_BAR_DEACTIVATED),
  _modificationPanel (true),
  _modificationMenuBar (true),
  _drawPanel (true),
  _drawMenuBar (true)
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


void Interface::drawPanel()
{
  if (_panelPosition == E_PANEL_DEACTIVATED)
  {
    g_status->setRenderX(WINDOW_SIZE_X);
    g_status->setGridOffsetX((WINDOW_SIZE_X - CELL_WIDTH * NB_COLUMNS) / 2);
    _modificationPanel = false;

    return;
  }

  // TODO draw the panel
  unsigned int render_x = 0.70f * WINDOW_SIZE_X;
  //  sf::Vertex line[2] = {
  //    sf::Vector2f (render_x, 0),
  //    sf::Vector2f (render_x, WINDOW_SIZE_Y)
  //  };
  //  WINDOW->draw(line, 2, sf::Lines);

  g_status->setRenderX(render_x);
  if (_panelPosition == E_PANEL_LEFT)
    g_status->setGridOffsetX(WINDOW_SIZE_X - render_x);
  else
    g_status->setGridOffsetX((render_x - CELL_WIDTH * NB_COLUMNS) / 2);

  _modificationPanel = false;
}


void Interface::drawMenuBar()
{
  DEBUG_PRINT_VALUE(_menuBarPosition);
  if (_menuBarPosition == E_MENU_BAR_DEACTIVATED)
  {
    g_status->setRenderY(WINDOW_SIZE_Y);
    g_status->setGridOffsetY((WINDOW_SIZE_Y - CELL_HEIGHT * NB_LINES) / 2);
    _modificationMenuBar = false;

    return;
  }

  // TODO draw the menuBar
  unsigned int render_y = WINDOW_SIZE_Y - CELL_HEIGHT / 2;
  //  sf::Vertex line[2] = {
  //    sf::Vector2f (0, render_y),
  //    sf::Vector2f (WINDOW_SIZE_X, render_y)
  //  };
  //  WINDOW->draw(line, 2, sf::Lines);

  g_status->setRenderY(WINDOW_SIZE_Y - render_y);

  unsigned int offset = (render_y - CELL_HEIGHT * NB_LINES) / 2;
  if (_menuBarPosition == E_MENU_BAR_BOTTOM)
    g_status->setGridOffsetY(offset);
  else
    g_status->setGridOffsetY(offset + CELL_HEIGHT / 2);

  _modificationMenuBar = false;
}


void Interface::draw()
{
  if (_modificationPanel)
    this->drawPanel();

  if (_modificationMenuBar)
    this->drawMenuBar();

  // if (_cursor->getVisible())
  _cursor->getSprite(GRID_OFFSET_X, GRID_OFFSET_Y);
  _cursor->draw();

  if (CURRENT_MODE == E_MODE_MOVING_UNIT || CURRENT_MODE == E_MODE_ACTION_MENU)
    _path->drawPath();

  if (CURRENT_MODE == E_MODE_SELECTION_MENU || CURRENT_MODE == E_MODE_ACTION_MENU)
    _inGameMenu->draw();
}
