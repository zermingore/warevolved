#include <input/KeyManager.hh>

#include <common/Settings.hh>
#include <common/enums/input.hh>
#include <debug/Debug.hh>


// Static members definition
std::multimap<const sf::Keyboard::Key, const e_key> KeyManager::_keys_mapping;
std::map<const e_key, const e_input> KeyManager::_events_mapping;
ThreadSafeQueue<e_input> KeyManager::_active_inputs;
sf::Clock KeyManager::_clock_events_freeze;
size_t KeyManager::_events_freeze_duration;



void KeyManager::Initialize()
{
  /// \todo Read configuration file to get these values (use Settings Class)

  // This mapping might be overloaded later, by the configuration management
  // keyboard: user part; e_key binary part
  // _keys_mapping: keyboard -> e_key ('z' and '8' can be used for LEFT key)
  // e_key -> keyboard (allow duplicated keys)

  _keys_mapping.insert({sf::Keyboard::Left, e_key::LEFT});


  // _keys_mapping.insert({e_key::LEFT      , sf::Keyboard::Left  });
  // _keys_mapping.insert({e_key::RIGHT     , sf::Keyboard::Right });
  // _keys_mapping.insert({e_key::UP        , sf::Keyboard::Up    });
  // _keys_mapping.insert({e_key::DOWN      , sf::Keyboard::Down  });

  // // These don't seem natural (but makes sense with a Workman layout)
  // _keys_mapping.insert({e_key::LEFT      , sf::Keyboard::N     });
  // _keys_mapping.insert({e_key::UP        , sf::Keyboard::E     });
  // _keys_mapping.insert({e_key::DOWN      , sf::Keyboard::O     });
  // _keys_mapping.insert({e_key::RIGHT     , sf::Keyboard::I     });

  // _keys_mapping.insert({e_key::SELECTION , sf::Keyboard::Space });
  // _keys_mapping.insert({e_key::EXIT      , sf::Keyboard::Escape});


  // This event mapping is populated here but will then be read only
  // These are the mapping key (dissociated from the keyboard) -> event
  _events_mapping.insert({e_key::LEFT      , e_input::MOVE_LEFT });
  _events_mapping.insert({e_key::RIGHT     , e_input::MOVE_RIGHT});
  _events_mapping.insert({e_key::UP        , e_input::MOVE_UP   });
  _events_mapping.insert({e_key::DOWN      , e_input::MOVE_DOWN });
  _events_mapping.insert({e_key::SELECTION , e_input::SELECTION });
  _events_mapping.insert({e_key::EXIT      , e_input::EXIT      });
}



void KeyManager::pushEvent(const sf::Keyboard::Key& key)
{
  PRINTF("pushing event");
  // PRINTF((*_keys_mapping.find(sf::Keyboard::Left)).second);

  // getting the logical key
  auto logical_key_it(_keys_mapping.find(key));
  if (logical_key_it == _keys_mapping.end())
  {
    PRINTF("Dropping unrecognized key", static_cast<int> (key));
    return;
  }
  auto logical_key(logical_key_it->second);


  _active_inputs.push(_events_mapping[logical_key]);


  /// \todo Still useful ?
  if (eventsFreezed()) {
    PRINTF("Freezed events (why?)");
    return;
  }
}



e_input KeyManager::popEvent()
{
  PRINTF("poping event...");

  return _active_inputs.pop();
}


void KeyManager::blockInputs(const size_t duration)
{
  PRINTF("Blocking inputs, why ?");
  return;

  // // Clearing active inputs
  // _active_inputs.clear();

  // // Relaunching the clock
  // _events_freeze_duration = duration;
  // _clock_events_freeze.restart();
}



bool KeyManager::eventsFreezed()
{
  // Check if the events were blocked for a minimal duration
  return (_clock_events_freeze.getElapsedTime().asMilliseconds()
          < static_cast<int> (_events_freeze_duration));
}
