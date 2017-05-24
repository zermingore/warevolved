#include <input/KeyManager.hh>
#include <common/Settings.hh>
#include <common/enums/input.hh>



KeyManager::KeyManager()
{
  /// \todo Read configuration file to get these values (use Settings Class)

  // This mapping might be overloaded later, by the configuration management
  // keyboard: user part; e_key binary part
  // _keys_mapping: keyboard -> e_key ('z' and '8' can be used for LEFT key)

  _keys_mapping.insert({e_key::LEFT      , sf::Keyboard::Left  });
  _keys_mapping.insert({e_key::RIGHT     , sf::Keyboard::Right });
  _keys_mapping.insert({e_key::UP        , sf::Keyboard::Up    });
  _keys_mapping.insert({e_key::DOWN      , sf::Keyboard::Down  });

  // These don't seem natural (but makes sense with a Workman layout)
  _keys_mapping.insert({e_key::LEFT      , sf::Keyboard::N     });
  _keys_mapping.insert({e_key::UP        , sf::Keyboard::E     });
  _keys_mapping.insert({e_key::DOWN      , sf::Keyboard::O     });
  _keys_mapping.insert({e_key::RIGHT     , sf::Keyboard::I     });

  _keys_mapping.insert({e_key::SELECTION , sf::Keyboard::Space });
  _keys_mapping.insert({e_key::EXIT      , sf::Keyboard::Escape});


  // This event mapping is populated here but will then be read only
  // These are the mapping key (dissociated from the keyboard) -> event
  _events_mapping.insert({e_key::LEFT      , e_input::MOVE_LEFT });
  _events_mapping.insert({e_key::RIGHT     , e_input::MOVE_RIGHT});
  _events_mapping.insert({e_key::UP        , e_input::MOVE_UP   });
  _events_mapping.insert({e_key::DOWN      , e_input::MOVE_DOWN });
  _events_mapping.insert({e_key::SELECTION , e_input::SELECTION });
  _events_mapping.insert({e_key::EXIT      , e_input::EXIT      });
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
  for (const auto& it: _keys_mapping)
  {
    if (sf::Keyboard::isKeyPressed(it.second))
    {
      _active_inputs.insert(_events_mapping[it.first]);
    }
  }
}



void KeyManager::blockInputs(const size_t duration)
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
          < static_cast<int> (_events_freeze_duration));
}
