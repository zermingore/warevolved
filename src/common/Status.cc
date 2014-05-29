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

Status::~Status()
{
  delete _window;

  while (!_states.empty())
  	_states.pop(); // calls element destructor
}

e_mode Status::currentMode()
{
  if (_states.empty())
  {
    DEBUG_PRINT("_states stack is empty, exiting...");
    return E_MODE_NONE;
  }

  return _states.top()->mode();
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
    CURSOR->setCoords(_states.top()->cursorCoords());

  _states.pop();
}


void Status::exitToMode(e_mode mode, bool skip)
{
  while (_states.top()->mode() != mode)
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
      CURSOR->setCoords(_states.top()->cursorCoords());
  }
}


State *Status::popCurrentMode()
{
  State *tmp = _states.top();
  _states.pop();

  return tmp;
}

Coords Status::selectedCell() {
  return _selectedCell;
}

void Status::cellSelection() {
	_selectedCell = CURSOR->coords();
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

void Status::setGridOffset()
{
  // offset = 1/2 left room
  _gridOffsetX = (_renderX - _cellWidth * _map->nbColumns()) / 2;
  _gridOffsetY = (_renderY - _cellHeight * _map->nbLines()) / 2;
}
