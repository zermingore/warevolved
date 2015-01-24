#include <interface/Interface.hh>
#include <common/globals.hh>


Interface::Interface() :
  _modificationPanel (true),
  _modificationMenuBar (true)
{
  _cursor = std::make_shared<Cursor> ();
  _path = std::make_shared<PathFinding> ();
  _inGameMenu = std::make_shared<InGameMenu> ();
  _panel = std::make_shared<SidePanel> ();
  _menuBar = std::make_shared<MenuBar> ();
}


void Interface::nextPanelPosition()
{
  // stores the actual one, before actualising
  _lastPanelPosition = _panel->incrementPosition();
  _modificationPanel = true;
}

void Interface::nextMenuBarPosition()
{
  // stores the actual one, before actualising
  _lastMenuBarPosition = _menuBar->incrementPosition();
  _modificationMenuBar = true;
}

void Interface::setSidePanel()
{
  if (_panel->position() == Panel_position::DEACTIVATED)
  {
    g_status->setRenderX(WINDOW_SIZE_X);
    g_status->setGridOffsetX((WINDOW_SIZE_X - CELL_WIDTH * NB_COLUMNS) / 2);
    _modificationPanel = false;

    return;
  }

  auto offset = 4 * CELL_WIDTH; // panel_width
  if (g_settings->fullScreen())
    offset *= 2;

  auto render_x = WINDOW_SIZE_X - offset;
  g_status->setRenderX(render_x);
  sf::Vector2f origin {0, 0};
  sf::Vector2f size = {
    (float) WINDOW_SIZE_X - render_x - (render_x - CELL_WIDTH * NB_COLUMNS) / 2,
    (float) WINDOW_SIZE_Y
  };

  if (_panel->position() == Panel_position::LEFT)
  {
    g_status->setGridOffsetX(offset + GRID_THICKNESS);
  }
  else
  {
    g_status->setGridOffsetX(
      (render_x - CELL_WIDTH * NB_COLUMNS) / 2 - 2 * GRID_THICKNESS);
    origin.x = WINDOW_SIZE_X - size.x;
  }

  if (_menuBar->position() == MenuBar_position::TOP)
  {
//    size.y -= _menuBar->size().y;
    origin.y += _menuBar->size().y;
  }
  if (_menuBar->position() == MenuBar_position::BOTTOM)
  {
    size.y -= _menuBar->size().y;
  }

  _panel->setSize(size);
  _panel->setOrigin(origin);
  _modificationPanel = false;
}


void Interface::setMenuBar()
{
  if (_menuBar->position() == MenuBar_position::DEACTIVATED)
  {
    g_status->setRenderY(WINDOW_SIZE_Y);
    g_status->setGridOffsetY((WINDOW_SIZE_Y - CELL_HEIGHT * NB_LINES) / 2);
    _modificationMenuBar = false;

    // redraw side panel if needed
    return;
  }

  unsigned int render_y = WINDOW_SIZE_Y - CELL_HEIGHT / 2;
  g_status->setRenderY(WINDOW_SIZE_Y - render_y);

  unsigned int offset = (render_y - CELL_HEIGHT * NB_LINES) / 2;
  if (_menuBar->position() == MenuBar_position::TOP)
  {
    g_status->setGridOffsetY(offset + CELL_HEIGHT / 2 - GRID_THICKNESS);
    sf::Vector2f size(WINDOW_SIZE_X, CELL_HEIGHT / 2);
    _menuBar->setSize(size);
    sf::Vector2f origin(0, 0);
    _menuBar->setOrigin(origin);
  }
  else
  {
    g_status->setGridOffsetY(offset - GRID_THICKNESS);
    sf::Vector2f size(WINDOW_SIZE_X, CELL_HEIGHT / 2);
    _menuBar->setSize(size);
    sf::Vector2f origin(0, WINDOW_SIZE_Y - size.y);
    _menuBar->setOrigin(origin);
  }

  _modificationMenuBar = false;
}


void Interface::drawSidePanel()
{
  if (_panel->position() == Panel_position::DEACTIVATED)
    return;

  _panel->draw();
}


void Interface::drawMenuBar()
{
  if (_menuBar->position() == MenuBar_position::DEACTIVATED)
    return;

  _menuBar->draw();
}


void Interface::draw()
{
  if (_modificationPanel)
    setSidePanel();

  if (_modificationMenuBar)
    setMenuBar();

  // if (_cursor->getVisible())
  _cursor->sprite(GRID_OFFSET_X, GRID_OFFSET_Y);
  _cursor->draw();

  drawSidePanel();
  drawMenuBar();

  if (CURRENT_MODE == E_MODE_MOVING_UNIT || CURRENT_MODE == E_MODE_ACTION_MENU)
    _path->drawPath();

  // TODO get right inGameMenu
  if (CURRENT_MODE == E_MODE_SELECTION_MENU || CURRENT_MODE == E_MODE_ACTION_MENU)
    _inGameMenu->draw();
}
