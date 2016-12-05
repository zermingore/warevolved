#include <common/Status.hh>
#include <game/applications/Battle.hh>
#include <game/Player.hh>
#include <context/StateFactory.hh>

#include <input/InputProcessor.hh>
#include <input/KeyManager.hh>


// Static class attributes definition
std::stack<std::shared_ptr<State>> Status::_states;
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


std::shared_ptr<State> Status::currentState()
{
  if (_states.empty()) {
    assert(! "_states stack is empty, exiting...");
  }

  return _states.top();
}


std::shared_ptr<State> Status::popCurrentState()
{
  auto tmp(_states.top());
  _states.pop();

  // Force ignoring current active inputs
  _inputProcessor->keyManager()->blockInputs();

  return tmp;
}


void Status::pushState(e_state state) {
  _states.push(StateFactory::createState(state));

  // Force ignoring current active inputs
  _inputProcessor->keyManager()->blockInputs();
}



std::shared_ptr<Player> Status::player() {
  return _battle->getCurrentPlayer();
}

std::shared_ptr<interface::Interface> Status::interface() {
  return _battle->getCurrentPlayer()->interface();
}
