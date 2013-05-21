#include <common/Status.hh>
#include <common/include.hh>


Status::Status() :
  _panelPosition (E_PANEL_DEACTIVATED),
  _menuBarPosition (E_MENU_BAR_DEACTIVATED),
  _eventMode (E_EVENT_IN_GAME),
  _selectionMode (false)
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

bool Status::getSelectionMode() {
  return _selectionMode;
}

e_event_mode Status::getEventMode() {
  return _eventMode;
}

sf::Vector2f Status::getSelectedCell() {
  return _selectedCell;
}

unsigned int Status::getSelectionMenuSelectedEntry() {
  return _selectionMenuSelectedEntry;
}


void Status::setSelectionMode(bool selection_mode) {
  _selectionMenuSelectedEntry = 0;
  _selectionMode = selection_mode;
}

void Status::setSelectionMenuSelectedEntry(unsigned int selected_entry) {
  _selectionMenuSelectedEntry = selected_entry;
}

void Status::cellSelection()
{
  if (!_selectionMode)
  {
	_selectedCell.x = _cursor->getX();
	_selectedCell.y = _cursor->getY();
  }

  // updating selection state
  _selectionMode = !_selectionMode;
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

void Status::setEventMode(e_event_mode event_mode) {
  _eventMode = event_mode;
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
