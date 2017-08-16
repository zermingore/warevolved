#include <common/Status.hh>

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



Status::~Status()
{
  while (!_states.empty()) {
    _states.pop(); // calls element destructor
  }
}


e_state Status::state()
{
  assert(!_states.empty() && "_states stack is empty, exiting...");

  return _states.top().first;
}


std::shared_ptr<State> Status::currentState()
{
  assert(!_states.empty() && "_states stack is empty, exiting...");

  return _states.top().second;
}


void Status::pushState(const e_state state)
{
  // suspend the current State
  if (!_states.empty()) {
    _states.top().second->suspend();
  }

  // push a new State
  auto new_state(StateFactory::createState(state));
  _states.push({state, new_state});
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
