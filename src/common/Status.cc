#include <common/enums/states.hh>
#include <common/Status.hh>
#include <common/include.hh>
#include <common/macros.hh>
#include <context/State.hh>
#include <game/applications/Battle.hh>
#include <game/Map.hh>
#include <game/Player.hh>
#include <input/EventManager.hh>
#include <context/StateFactory.hh>
#include <interface/Interface.hh>


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


std::shared_ptr<State> Status::currentState()
{
  if (_states.empty()) {
    assert(! "_states stack is empty, exiting...");
  }

  return _states.top();
}


void Status::exitCurrentState()
{
  _states.pop();
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



std::shared_ptr<Player> Status::player() {
  return _battle->getCurrentPlayer();
}

std::shared_ptr<interface::Interface> Status::interface() {
  return _battle->getCurrentPlayer()->interface();
}
