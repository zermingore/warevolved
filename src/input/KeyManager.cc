#include <input/KeyManager.hh>
#include <common/Settings.hh>
#include <common/enums/input.hh>


KeyManager::KeyManager()
{
  /// \todo Read configuration file to retrieve these values (use Settings Class)

  _keys_mapping.insert({sf::Keyboard::Left, e_key::E_KEY_LEFT});

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


bool KeyManager::ready(e_timer index)
{
//  if (_clocks[index].getElapsedTime().asMilliseconds() > Settings::keyRepeatDelay())
//    restartTimer(index);

//  return (_ready[index]);
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
