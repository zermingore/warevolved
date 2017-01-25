#include <common/Status.hh>
#include <game/applications/Battle.hh>
#include <game/Player.hh>
#include <context/StateFactory.hh>
#include <input/InputProcessor.hh>
#include <input/KeyManager.hh>


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


void Status::pushState(e_state state)
{
  // suspend the current State
  if (!_states.empty()) {
    _states.top().second->suspend();
  }

  // push a new State
  auto new_state(StateFactory::createState(state));
  _states.push({state, new_state});
  new_state->resume();

  // Force ignoring current active inputs
  _inputProcessor->keyManager()->blockInputs();

  // auto i(std::make_shared<int> (1));
  // auto str(std::make_shared<std::string> ("abc"));
  // _states.top().second->setAttributes(i, str);
}


void Status::popCurrentState()
{
  assert(!_states.empty() && "No State found trying to pop States");
  _states.pop();

  // Force ignoring current active inputs
  _inputProcessor->keyManager()->blockInputs();


  if (!_states.empty()) {
    PRINTF("<< new State:", (int) _states.top().first);
  }
}


void Status::clearStates()
{
  assert(!_states.empty() && "clearStates called with empty stack");

  while (_states.top().first != e_state::PLAYING) {
    popCurrentState();
  }
}


std::shared_ptr<Player> Status::player() {
  return _battle->getCurrentPlayer();
}

std::shared_ptr<interface::Interface> Status::interface() {
  return _battle->getCurrentPlayer()->interface();
}
