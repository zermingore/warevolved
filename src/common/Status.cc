#include <common/Status.hh>
#include <common/include.hh>


Status::Status() :
  _window (NULL),
  _cursor (NULL),
  _map (NULL),
  _panelPosition (E_PANEL_DEACTIVATED),
  _menuBarPosition (E_MENU_BAR_DEACTIVATED),
  _currentFPS (0),
  _cellWidth (0),
  _cellHeight (0),
  _gridThickness (0),
  _gridOffsetX (0),
  _gridOffsetY (0),
  _renderX (0),
  _renderY (0)
{
}

Status::~Status() {
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

e_mode Status::getCurrentMode()
{
  if (_states.empty())
  {
    DEBUG_PRINT("_states stack is empty, exiting...");
    return E_MODE_NONE;
  }

  return _states.top()->getMode();
}

void Status::pushMode(e_mode mode) {
  _states.push(new State (mode));
}

void Status::exitCurrentMode()
{
  if (_states.empty())
  {
    // TODO exit properly (at least with debug_leaks flag)
    DEBUG_PRINT("invalid State stack usage, exiting...");
#   ifndef DEBUG
    std::exit(1);
#   endif
    return;
  }

  if (_cursor)
    _cursor->setCoords(_states.top()->getCursorCoords());

  _states.pop();
}


Coords Status::getSelectedCell() {
  return _selectedCell;
}

void Status::cellSelection() {
	_selectedCell = _cursor->getCoords();
}

sf::RenderWindow *Status::getWindow() {
  return _window;
}

Map *Status::getMap() {
  return _map;
}

float Status::getCurrentFPS() {
  return _currentFPS;
}

unsigned int Status::getCellWidth() {
  return _cellWidth;
}

unsigned int Status::getCellHeight() {
 return _cellHeight;
}

unsigned int Status::getGridThickness() {
 return _gridThickness;
}

unsigned int Status::getRenderX() {
 return _renderX;
}

unsigned int Status::getRenderY() {
 return _renderY;
}

unsigned int Status::getGridOffsetX() {
  return _gridOffsetX;
}

unsigned int Status::getGridOffsetY() {
  return _gridOffsetY;
}


void Status::setWindow(sf::RenderWindow *window)
{
  _window = window;

  // initialize render room
  _renderX = _window->getSize().x;
  _renderY = _window->getSize().y;
}

void Status::setCursor(Cursor *cursor) {
  _cursor = cursor;
}

void Status::setMap(Map *map) {
  _map = map;
}

void Status::setSelectedCell(Coords selected_cell) {
  _selectedCell = selected_cell;
}

void Status::setCurrentFPS(float current_fps) {
  _currentFPS = current_fps;
}

void Status::setCellWidth(unsigned int cell_width) {
  _cellWidth = cell_width;
}

void Status::setCellHeight(unsigned int cell_height) {
  _cellHeight = cell_height;
}

void Status::setGridThickness(unsigned int grid_thickness) {
  _gridThickness = grid_thickness;
}

void Status::setRenderX(unsigned int render_x) {
 _renderX = render_x;
}

void Status::setRenderY(unsigned int render_y) {
 _renderY = render_y;
}

void Status::setGridOffsetX(unsigned int grid_offset_x) {
  _gridOffsetX = grid_offset_x;
}

void Status::setGridOffsetY(unsigned int grid_offset_y) {
  _gridOffsetY = grid_offset_y;
}
