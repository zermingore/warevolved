#include <algorithm>
#include <input/KeyManager.hh>
#include <common/Settings.hh>
#include <common/enums/input.hh>



KeyManager::KeyManager()
{
  /// \todo Read configuration file to retrieve these values (use Settings Class)

  /// \todo lambda / macro map_key(sf, e_key)

 // directions
 _keys_mapping.insert({sf::Keyboard::Left,   e_key::E_KEY_LEFT});
 _keys_mapping.insert({sf::Keyboard::Right,  e_key::E_KEY_RIGHT});
 _keys_mapping.insert({sf::Keyboard::Up,     e_key::E_KEY_UP});
 _keys_mapping.insert({sf::Keyboard::Down,   e_key::E_KEY_DOWN});
 _keys_mapping.insert({sf::Keyboard::Space,  e_key::E_KEY_SELECTION_1});
 _keys_mapping.insert({sf::Keyboard::Escape, e_key::E_KEY_EXIT_1});

  // should be e_key -> e_input
  // _events_mapping.insert({_keys_mapping[sf::Keyboard::Left], e_input::MOVE_LEFT_1});

  _events_mapping.insert({sf::Keyboard::Left,   e_input::MOVE_LEFT_1});
  _events_mapping.insert({sf::Keyboard::Right,  e_input::MOVE_RIGHT_1});
  _events_mapping.insert({sf::Keyboard::Up,     e_input::MOVE_UP_1});
  _events_mapping.insert({sf::Keyboard::Down,   e_input::MOVE_DOWN_1});
  _events_mapping.insert({sf::Keyboard::Space,  e_input::SELECTION_1});
  _events_mapping.insert({sf::Keyboard::Escape, e_input::EXIT_1});
}



void KeyManager::populateEvents()
{
  // Clear the active inputs list
  _active_inputs.clear();

  // If the inputs are disabled, return, leaving an empty active input array
  if (eventsFreezed()) {
    return;
  }

  // Add every event which key is pressed
  for (const auto& it: _events_mapping)
  {
    if (sf::Keyboard::isKeyPressed(it.first)) {
      _active_inputs.push_back(it.second);
    }
  }
}



void KeyManager::blockInputs(unsigned int duration)
{
  // Clearing active inputs
  _active_inputs.clear();

  // Relaunching the clock
  _events_freeze_duration = duration;
  _clock_events_freeze.restart();
}



bool KeyManager::eventsFreezed()
{
  // Check if the events were blocked for a minimal duration
  return (_clock_events_freeze.getElapsedTime().asMilliseconds()
          < _events_freeze_duration);
}
