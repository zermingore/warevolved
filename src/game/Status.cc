/**
 * \file
 * \date April 18, 2013
 * \author Zermingore
 * \brief Global game status accessor, including current Player, State, ...
 */

#include <cassert>

#include <context/StatesFactory.hh>
#include <game/Battle.hh>
#include <game/Player.hh>
#include <game/Status.hh>
#include <input/EventManager.hh>
#include <input/KeyManager.hh>

#include <debug/Debug.hh>


namespace game {



e_state Status::state()
{
  assert(!_states.empty() && "_states stack is empty");
  return _states.top().first;
}



void Status::resumeState()
{
  assert(!_states.empty() && "_states stack is empty");
  _states.top().second->resume();
}



void Status::drawState()
{
  _lock.try_lock(); ///< \todo Explain this try_lock + unconditional unlock
  _states.top().second->draw();
  _lock.unlock();
}



bool Status::processInput(const e_input& input)
{
  _lock.lock();
  auto ret {_states.top().second->eventManager()->process(input)};
  _lock.unlock();
  return ret;
}



void Status::pushState(const e_state state)
{
  _lock.lock();

  // suspend the current State
  if (!_states.empty()) {
    _states.top().second->suspend();
  }

  // push a new State
  _states.push({state, StatesFactory::createState(state)});

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

  while (_states.top().first != e_state::PLAYING)
  {
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



std::shared_ptr<Player> Status::player()
{
  return _battle->getCurrentPlayer();
}

std::shared_ptr<interface::Interface> Status::interface()
{
  return _battle->getCurrentPlayer()->interface();
}


} // namespace game
