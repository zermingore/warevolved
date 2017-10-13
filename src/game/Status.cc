#include <game/Status.hh>

#include <cassert>

#include <game/Battle.hh>
#include <game/Player.hh>
#include <context/StateFactory.hh>
#include <input/KeyManager.hh>


namespace game {


// Static class attributes definition
std::stack<std::pair<e_state, std::shared_ptr<State>>> Status::_states;
std::shared_ptr<Battle> Status::_battle;
std::shared_ptr<InputProcessor> Status::_inputProcessor;
Coords Status::_selectedCell;
Coords Status::_selectedUnitPosition;
bool Status::_pushingState = false;



e_state Status::state()
{
  assert(!_states.empty() && "_states stack is empty");

  return _states.top().first;
}


std::shared_ptr<State> Status::currentState()
{
  // Active waiting...
  while (_pushingState)
    ;

  assert(!_states.empty() && "_states stack is empty");

  return _states.top().second;
}


void Status::pushState(const e_state state)
{
  _pushingState = true;
  // suspend the current State
  if (!_states.empty()) {
    _states.top().second->suspend();
  }

  // push a new State
  auto new_state(StateFactory::createState(state));
  _states.push({state, new_state});
  _pushingState = false;
}


void Status::popCurrentState()
{
  assert(!_states.empty() && "No State found trying to pop States");
  _states.pop();
}


void Status::clearStates()
{
  assert(!_states.empty() && "clearStates called with empty stack");

  while (_states.top().first != e_state::PLAYING) {
    popCurrentState();
  }
}


void Status::nextPlayer()
{
  // Clearing states, totaly
  _battle->nextPlayer();
  clearStates();
  popCurrentState();

  /// \todo manage IA case: do not push a new state playing
  pushState(e_state::PLAYING);
}



std::shared_ptr<Player> Status::player() {
  return _battle->getCurrentPlayer();
}

std::shared_ptr<interface::Interface> Status::interface() {
  return _battle->getCurrentPlayer()->interface();
}


} // namespace game
