#include <interface/Interface.hh>
#include <common/Status.hh>


Interface::Interface()
  : _panelPosition (panel_position::DEACTIVATED)
  , _menuBarPosition (menu_bar_position::DEACTIVATED)
  , _modificationPanel (true)
  , _modificationMenuBar (true)
{
  _cursor = std::make_shared<Cursor> ();
  //  _path = std::make_shared<PathFinding> ();
  //  _inGameMenu = std::make_shared<InGameMenu> ();
  //  _panel = std::make_shared<SidePanel> ();
  //  _menuBar = std::make_shared<MenuBar> ();
}

void Interface::incrementPanelPosition()
{
  // Loops over the panel::NB_POSITIONS possibilities.
  _panelPosition = static_cast<panel_position>
    ((static_cast<int> (_panelPosition) + 1) % static_cast<int> (panel_position::NB_POSITIONS));
  _modificationPanel = true;
}

void Interface::incrementMenuBarPosition()
{
  // Loops over the menu_bar::NB_POSITIONS possibilities.
  _menuBarPosition = static_cast<menu_bar_position>
    ((static_cast<int> (_menuBarPosition) + 1) % static_cast<int> (menu_bar_position::NB_POSITIONS));
  _modificationMenuBar = true;
}

void Interface::setSidePanel()
{
//   if (_panelPosition == panel_position::DEACTIVATED)
//   {
//     Status::setRenderX(WINDOW_SIZE_X);
//     g_status->setGridOffsetX((WINDOW_SIZE_X - CELL_WIDTH * NB_COLUMNS) / 2);
//     _modificationPanel = false;

//     return;
//   }

//   auto offset = 4 * CELL_WIDTH; // panel_width
//   if (g_settings->fullScreen())
//     offset *= 2;

//   auto render_x = WINDOW_SIZE_X - offset;
//   g_status->setRenderX(render_x);
//   sf::Vector2f origin {0, 0};
//   sf::Vector2f size = {
//     (float) WINDOW_SIZE_X - render_x - (render_x - CELL_WIDTH * NB_COLUMNS) / 2,
//     (float) WINDOW_SIZE_Y
//   };

//   if (_panelPosition == panel_position::LEFT)
//   {
//     g_status->setGridOffsetX(offset + GRID_THICKNESS);
//   }
//   else
//   {
//     g_status->setGridOffsetX(
//       (render_x - CELL_WIDTH * NB_COLUMNS) / 2 - 2 * GRID_THICKNESS);
//     origin.x = WINDOW_SIZE_X - size.x;
//   }

//   if (_menuBarPosition == menu_bar_position::TOP)
//   {
// //    size.y -= _menuBar->size().y;
//     origin.y += _menuBar->size().y;
//   }
//   if (_menuBarPosition == menu_bar_position::BOTTOM)
//   {
//     size.y -= _menuBar->size().y;
//   }

//   _panel->setSize(size);
//   _panel->setOrigin(origin);
//   _modificationPanel = false;
}


void Interface::setMenuBar()
{
  // if (_menuBarPosition == E_MENU_BAR_DEACTIVATED)
  // {
  //   g_status->setRenderY(WINDOW_SIZE_Y);
  //   g_status->setGridOffsetY((WINDOW_SIZE_Y - CELL_HEIGHT * NB_LINES) / 2);
  //   _modificationMenuBar = false;

  //   // redraw side panel if needed
  //   return;
  // }

  // unsigned int render_y = WINDOW_SIZE_Y - CELL_HEIGHT / 2;
  // g_status->setRenderY(WINDOW_SIZE_Y - render_y);

  // unsigned int offset = (render_y - CELL_HEIGHT * NB_LINES) / 2;
  // if (_menuBarPosition == menu_bar_position::TOP)
  // {
  //   g_status->setGridOffsetY(offset + CELL_HEIGHT / 2 - GRID_THICKNESS);
  //   sf::Vector2f size(WINDOW_SIZE_X, CELL_HEIGHT / 2);
  //   _menuBar->setSize(size);
  //   sf::Vector2f origin(0, 0);
  //   _menuBar->setOrigin(origin);
  // }
  // else
  // {
  //   g_status->setGridOffsetY(offset - GRID_THICKNESS);
  //   sf::Vector2f size(WINDOW_SIZE_X, CELL_HEIGHT / 2);
  //   _menuBar->setSize(size);
  //   sf::Vector2f origin(0, WINDOW_SIZE_Y - size.y);
  //   _menuBar->setOrigin(origin);
  // }

  // _modificationMenuBar = false;
}


//void Interface::drawSidePanel()
//{
//  if (_panelPosition == panel_position::DEACTIVATED)
//    return;

//  _panel->draw();
//}


//void Interface::drawMenuBar()
//{
//  if (_menuBarPosition == menu_bar_position::DEACTIVATED)
//    return;

//  _menuBar->draw();
//}


void Interface::buildElements()
{
//  if (_modificationPanel)
//    setSidePanel();

//  if (_modificationMenuBar)
//    setMenuBar();

  InterfaceElement elt("cursor");
  elt.setPosition(_cursor->coords());
  elt.setRotation(45.);
  elt.setScale(.1);

  _elts.push_back(elt);

  //  auto mode = Status::currentMode();
  // if (mode == mode::MOVING_UNIT || mode == mode::ACTION_MENU)
  //   _path->drawPath();

  /// \todo get right inGameMenu
  //  if (mode == e_mode::SELECTION_MENU || mode == e_mode::ACTION_MENU)
  //    _inGameMenu->draw();
}
