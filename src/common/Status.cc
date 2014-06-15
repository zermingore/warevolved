#include <common/Status.hh>
#include <common/include.hh>
#include <common/macros.hh>
#include <common/globals.hh>


Status::Status() :
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
  while (!_states.empty())
  	_states.pop(); // calls element destructor
}

void Status::cellSelection() {
  _selectedCell = CURSOR->coords();
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

void Status::pushMode(e_mode mode)
{
  _states.push(std::make_shared<State> (mode));
}

void Status::pushModeInGameMenu(e_mode mode, InGameMenu *menu)
{
  menu->build(mode);
  _states.push(std::make_shared<State> (mode, menu));
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
      PRINTF("exitToMode failure: _states stack is empty");
      return;
    }
#   endif
    _states.pop();

    if (!skip && CURSOR)
      CURSOR->setCoords(_states.top()->cursorCoords());
  }
}

State Status::popCurrentMode()
{
  auto tmp(_states.top());
  _states.pop();

  return *tmp;
}

void Status::setWindow(std::unique_ptr<sf::RenderWindow> window)
{
  g_window = std::move(window);

  // initialize render room
  resetRender();
}

void Status::setGridOffset()
{
  // offset = 1/2 left room
  _gridOffsetX = (_renderX - _cellWidth * NB_COLUMNS) / 2;
  _gridOffsetY = (_renderY - _cellHeight * NB_LINES) / 2;
}

void Status::resetRender()
{
  _renderX = WINDOW_SIZE_X;
  _renderY = WINDOW_SIZE_Y;
}
