#include <common/Status.hh>
#include <common/include.hh>
#include <common/macros.hh>
#include <common/State.hh>
#include <interface/menus/InGameMenu.hh>
#include <game/applications/Battle.hh>
#include <game/Map.hh>


// Static class attributes definition
std::stack<std::shared_ptr<State>> _states;
std::shared_ptr<Battle> _battle;
Coords _selectedCell;
Coords _selectedUnitPosition;


Status::~Status()
{
  while (!_states.empty())
    _states.pop(); // calls element destructor
}

void Status::initialize()
{
  _selectedUnitPosition = Coords(-1, -1);
}

// void Status::cellSelection()
// {
//   _selectedCell = _battle->map()->cursor(_battle->currentPlayer())->coords();
// }


e_mode Status::currentMode()
{
  if (_states.empty())
  {
    DEBUG_PRINT("_states stack is empty, exiting...");
    return e_mode::NONE;
  }

  return _states.top()->currentMode();
}

std::shared_ptr<State> Status::currentState()
{
  if (_states.empty())
  {
    DEBUG_PRINT("_states stack is empty, exiting...");
  }

  return _states.top();
}

void Status::pushModeInGameMenu(e_mode mode, std::shared_ptr<InGameMenu> menu)
{
  menu->build(mode);
  _states.push(std::make_shared<State> (State(mode, menu)));
}


void Status::exitCurrentMode(const bool skip)
{
  if (skip)
  {
    _states.pop();
    return;
  }

  _battle->map()->setCursorCoords(_states.top()->cursorCoords());
  _states.pop();
}


void Status::exitToMode(e_mode mode, bool skip)
{
  while (_states.top()->currentMode() != mode)
  {
    _states.pop();

    if (!skip)
      _battle->map()->setCursorCoords(_states.top()->cursorCoords());
  }
}


std::shared_ptr<State> Status::popCurrentMode()
{
  auto tmp(_states.top());
  _states.pop();

  return tmp;
}


void Status::pushMode(e_mode mode) {
  _states.push(std::make_shared<State> (State(mode)));
}
