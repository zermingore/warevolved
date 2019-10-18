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
Coords Status::_selectedCell;
Coords Status::_selectedUnitPosition;
std::mutex Status::_lock;


e_state Status::state()
{
  _lock.lock();
  assert(!_states.empty() && "_states stack is empty");

  auto state_index(_states.top().first);
  _lock.unlock();

  return state_index;
}


std::shared_ptr<State> Status::currentState()
{
  _lock.lock();
  assert(!_states.empty() && "_states stack is empty");

  auto state(_states.top().second);
  _lock.unlock();

  return state;
}


void Status::pushState(const e_state state)
{
  _lock.lock();

  // suspend the current State
  if (!_states.empty()) {
    _states.top().second->suspend();
  }

  // push a new State
  auto new_state(StateFactory::createState(state));
  _states.push({state, new_state});

  _lock.unlock();
}


void Status::popCurrentState()
{
  _lock.lock();

  assert(!_states.empty() && "No State found trying to pop States");
  _states.pop();

  _lock.unlock();
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
