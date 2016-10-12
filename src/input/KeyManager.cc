#include <input/KeyManager.hh>
#include <common/Settings.hh>
#include <common/enums/input.hh>


KeyManager::KeyManager()
{
  /// \todo Read configuration file to retrieve these values (use Settings Class)

  /// \todo lambda / macro map_key(sf, e_key)

  _keys_mapping.insert({sf::Keyboard::Left, e_key::E_KEY_LEFT});
  _keys_mapping.insert({sf::Keyboard::Right, e_key::E_KEY_RIGHT});

  _events_mapping.insert({sf::Keyboard::Left, e_input::MOVE_LEFT_1});
  _events_mapping.insert({sf::Keyboard::Right, e_input::MOVE_RIGHT_1});

//  // directions
//  _keys_mapping.insert({sf::Keyboard::Up, {e_input::MOVE_UP_1}});
//  _keys_mapping.insert({sf::Keyboard::W, {e_input::MOVE_UP_2}});

//  _keys_mapping.insert({sf::Keyboard::Down, {e_input::MOVE_DOWN_1}});
//  _keys_mapping.insert({sf::Keyboard::S, {e_input::MOVE_DOWN_2}});

//  _keys_mapping.insert({sf::Keyboard::Left, {e_input::MOVE_LEFT_1}});
//  _keys_mapping.insert({sf::Keyboard::A, {e_input::MOVE_LEFT_2}});

//  _keys_mapping.insert({sf::Keyboard::Right, {e_input::MOVE_RIGHT_1}});
//  _keys_mapping.insert({sf::Keyboard::D, {e_input::MOVE_RIGHT_2}});

//  // action keys
//  _keys_mapping.insert({sf::Keyboard::Space, {e_input::SELECTION_1}});
//  _keys_mapping.insert({sf::Keyboard::Return, {e_input::SELECTION_2}});

//  // exit request keys
//  _keys_mapping.insert({sf::Keyboard::Escape, {e_input::EXIT_1}});
//  _keys_mapping.insert({sf::Keyboard::Escape, {e_input::EXIT_2}});
}


void KeyManager::populateEvents()
{
  _active_inputs.clear();
  for (const auto& it: _events_mapping)
  {
    if (sf::Keyboard::isKeyPressed(it.first))
      _active_inputs.push_back(it.second);
  }
}


// e_key > e_input > e_event
//   > LEFT > MOVE_LEFT
//   > LEFT > CURSOR_LEFT
// => should check if a e_event is active
bool KeyManager::isActive(e_input e)
{
  // if (sf::Keyboard::isKeyPressed(binding[e]))
  std::cout << "isActive()" << std::endl;

  return true; // SIGILL, again !?
}



void KeyManager::restartTimer(e_timer index)
{
//  _clocks[index].restart();
//  _ready[index] = true;
}


void KeyManager::resetSwitches()
{
//  if (!PRESSED(E_KEY_SELECTION))
//    _switches[E_SWITCH_SELECTION] = OFF;

//  if (!PRESSED(E_KEY_MENUBAR))
//    _switches[E_SWITCH_MENUBAR] = OFF;

//  if (!PRESSED(E_KEY_PANEL))
//    _switches[E_SWITCH_PANEL] = OFF;

//  if (!PRESSED(E_KEY_EXIT))
//    _switches[E_SWITCH_EXIT] = OFF;
}



//void EventManager::releasedKeys()
//{
  // The timer we want to reset must not match a pressed key
  // (in case 2 keys are pressed simultaneously)

//  if (!_km->up())
//    _km->restartTimer(E_TIMER_MOVE_UP);

//  if (!_km->down())
//    _km->restartTimer(E_TIMER_MOVE_DOWN);

//  if (!_km->left())
//    _km->restartTimer(E_TIMER_MOVE_LEFT);

//  if (!_km->right())
//    _km->restartTimer(E_TIMER_MOVE_RIGHT);

//  _km->resetSwitches();
//}
