#include <common/Status.hh>
#include <common/include.hh>
#include <common/macros.hh>
#include <common/globals.hh>


Status::Status() :
  _window (nullptr),
  _map (nullptr),
  _currentFPS (0),
  _cellWidth (0),
  _cellHeight (0),
  _gridThickness (0),
  _gridOffsetX (0),
  _gridOffsetY (0),
  _renderX (0),
  _renderY (0),
  _currentPlayer (0)
{
}

Status::~Status() {
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

void Status::pushModeInGameMenu(e_mode mode, InGameMenu *menu)
{
  menu->build(mode);
  _states.push(new State (mode, menu));
}


void Status::exitCurrentMode(bool skip)
{
  if (skip)
  {
    _states.pop();
    return;
  }

  if (CURSOR)
    CURSOR->setCoords(_states.top()->getCursorCoords());

  _states.pop();
}


void Status::exitToMode(e_mode mode, bool skip)
{
  while (_states.top()->getMode() != mode)
  {
#   ifdef DEBUG
    if (_states.empty())
    {
      DEBUG_PRINT("exitToMode failure: _states stack is empty");
      return;
    }
#   endif
    _states.pop();

    if (!skip && CURSOR)
      CURSOR->setCoords(_states.top()->getCursorCoords());
  }
}


State *Status::popCurrentMode()
{
  State *tmp = _states.top();
  _states.pop();

  return tmp;
}

Coords Status::getSelectedCell() {
  return _selectedCell;
}

void Status::cellSelection() {
	_selectedCell = CURSOR->getCoords();
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

unsigned int Status::getCurrentPlayer() {
  return _currentPlayer;
}

std::vector<Player*> Status::getPlayers() {
  return _players;
}

void Status::resetRender()
{
  _renderX = WINDOW_SIZE_X;
  _renderY = WINDOW_SIZE_Y;
}

void Status::setWindow(sf::RenderWindow *window)
{
  _window = window;

  // initialize render room
  this->resetRender();
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

void Status::setGridOffset()
{
  // offset = 1/2 left room
  _gridOffsetX = (_renderX - _cellWidth * _map->getNbColumns()) / 2;
  _gridOffsetY = (_renderY - _cellHeight * _map->getNbLines()) / 2;
}

void Status::setPlayers(std::vector<Player*> players) {
  _players = players;
}
