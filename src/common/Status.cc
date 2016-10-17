#include <common/enums/states.hh>
#include <common/Status.hh>
#include <common/include.hh>
#include <common/macros.hh>
#include <context/State.hh>
#include <context/StatePlaying.hh>
#include <interface/menus/InGameMenu.hh>
#include <game/applications/Battle.hh>
#include <game/Map.hh>
#include <input/EventManager.hh>
#include <context/StateFactory.hh>


// Static class attributes definition
std::stack<std::shared_ptr<State>> Status::_states;
std::shared_ptr<Battle> Status::_battle;
Coords Status::_selectedCell;
Coords Status::_selectedUnitPosition;


Status::~Status()
{
  while (!_states.empty()) {
    _states.pop(); // calls element destructor
  }
}


void Status::initialize()
{
  _selectedUnitPosition = Coords(-1, -1);
}

// void Status::cellSelection()
// {
//   _selectedCell = _battle->map()->cursor(_battle->currentPlayer())->coords();
// }


// e_state Status::currentState()
// {
//   if (_states.empty())
//   {
//     DEBUG_PRINT("_states stack is empty, exiting...");
//     return e_state::NONE;
//   }

//   return _states.top()->currentState();
// }


std::shared_ptr<State> Status::currentState()
{
  if (_states.empty()) {
    assert(false && "_states stack is empty, exiting...");
  }

  return _states.top();
}


void Status::pushStateInGameMenu(std::shared_ptr<InGameMenu> menu)
{
  menu->build(/*state*/);
  // _states.push(std::make_shared<StateInGameMenu> ());
}


void Status::exitCurrentState(const bool skip)
{
  if (skip)
  {
    _states.pop();
    return;
  }

//  if (_battle)
//    _battle->map()->setCursorCoords(_states.top()->cursorCoords());

  _states.pop();
}


void Status::exitToState(e_state state, bool skip)
{
  while (_states.top()->currentState() != state)
  {
    _states.pop();

//    if (!skip)
//      _battle->map()->setCursorCoords(_states.top()->cursorCoords());
  }
}


std::shared_ptr<State> Status::popCurrentState()
{
  auto tmp(_states.top());
  _states.pop();

  return tmp;
}


void Status::pushState(e_state state) {
  _states.push(StateFactory::createState(state));
}
