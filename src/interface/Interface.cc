#include <interface/Interface.hh>
#include <common/globals.hh>


Interface::Interface() :
  _panelPosition (E_PANEL_DEACTIVATED),
  _menuBarPosition (E_MENU_BAR_DEACTIVATED),
  _modificationPanel (true),
  _modificationMenuBar (true),
  _panelX (0),
  _menuBarY (0)
{
  _cursor = std::make_shared<Cursor> ();
  _path = std::make_shared<PathFinding> ();
  _inGameMenu = std::make_shared<InGameMenu> ();
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

  auto offset = 4 * CELL_WIDTH;
  if (g_settings->fullScreen())
    offset *= 2;

  auto render_x = WINDOW_SIZE_X - offset;
  g_status->setRenderX(render_x);
  if (_panelPosition == E_PANEL_LEFT)
  {
    g_status->setGridOffsetX(offset + GRID_THICKNESS);
    _panelX = WINDOW_SIZE_X - render_x - (render_x - CELL_WIDTH * NB_COLUMNS) / 2;
  }
  else
  {
    g_status->setGridOffsetX(
      (render_x - CELL_WIDTH * NB_COLUMNS) / 2 - 2 * GRID_THICKNESS);
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
  g_window->draw(line, 2, sf::Lines);

  std::shared_ptr<Unit> unit(MAP.unit(CURSOR->coords()));
  if (unit)
    PRINTF(unit->name());
}


void Interface::drawMenuBar()
{
  if (_menuBarPosition == E_MENU_BAR_DEACTIVATED)
    return;

  sf::Vertex line[2] = {
    sf::Vector2f(0, _menuBarY),
    sf::Vector2f(WINDOW_SIZE_X, _menuBarY)
  };
  g_window->draw(line, 2, sf::Lines);
}


void Interface::draw()
{
  if (_modificationPanel)
    setPanel();

  if (_modificationMenuBar)
    setMenuBar();

  // if (_cursor->getVisible())
  _cursor->sprite(GRID_OFFSET_X, GRID_OFFSET_Y);
  _cursor->draw();

  drawPanel();
  drawMenuBar();

  if (CURRENT_MODE == E_MODE_MOVING_UNIT || CURRENT_MODE == E_MODE_ACTION_MENU)
    _path->drawPath();

  // TODO get right inGameMenu
  if (CURRENT_MODE == E_MODE_SELECTION_MENU || CURRENT_MODE == E_MODE_ACTION_MENU)
    _inGameMenu->draw();
}
