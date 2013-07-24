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
  _renderY (0),
  _cursorSaveX (0),
  _cursorSaveY (0)
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
  if (_modes.empty())
  {
    DEBUG_PRINT("_modes stack is empty, exiting");
    return E_MODE_NONE;
  }

  if (!_cursorCoords.empty())
    _cursorCoords.pop();

  return _modes.top();
}


e_mode Status::getCurrentMode(int &x, int &y)
{
  if (_modes.empty())
  {
    DEBUG_PRINT("_modes stack is empty, exiting");
    return E_MODE_NONE;
  }

  if (!_cursorCoords.empty())
  {
    sf::Vector2f tmp = _cursorCoords.top();
    x = tmp.x;
    y = tmp.y;
    _cursorCoords.pop();
  }

  return _modes.top();
}


void Status::pushMode(e_mode mode)
{
	_modes.push(mode);
	if (_cursor) //  && _modes.top() != E_MODE_MOVING_UNIT
	{
    _cursorSaveX = _cursor->getX();
    _cursorSaveY = _cursor->getY();

    sf::Vector2f tmp(static_cast<float> (_cursor->getX()), static_cast<float> (_cursor->getY()));
    _cursorCoords.push(tmp);
	}
}

void Status::exitCurrentMode()
{
	if (_modes.empty())
		return;//std::exit(0); // TODO exit properly (at least with debug_leaks flag)

	_modes.pop();

	if (_cursorCoords.empty())
	  return;

  sf::Vector2f tmp = _cursorCoords.top();
  _cursorSaveX = tmp.x;
  _cursorSaveY = tmp.y;

  if (_cursor)
  {
    _cursor->setX(_cursorSaveX);
    _cursor->setY(_cursorSaveY);
  }
}


sf::Vector2f Status::getSelectedCell() {
  return _selectedCell;
}

void Status::cellSelection()
{
	_selectedCell.x = _cursor->getX();
	_selectedCell.y = _cursor->getY();
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

void Status::setSelectedCell(sf::Vector2f selected_cell) {
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
