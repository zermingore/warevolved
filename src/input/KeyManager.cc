/**
 * \file
 * \date April 17, 2013
 * \author Zermingore
 * \brief KeyManager class definition
 */

#include <input/KeyManager.hh>

#include <debug/Debug.hh>
#include <input/EventManager.hh>
#include <input/ReplayManager.hh>
#include <utility>


// Static members definition
std::multimap<const sf::Keyboard::Key, const e_key> KeyManager::_keys_mapping;
std::map<const e_key, const e_input> KeyManager::_events_mapping;
ThreadSafeQueue<e_input> KeyManager::_active_inputs;
std::shared_ptr<ReplayManager> KeyManager::_replay;



void KeyManager::Initialize(std::shared_ptr<ReplayManager> replay)
{
  _replay = std::move(replay);

  /// \todo Read configuration file to get these values (use Settings Class)

  // This mapping might be overloaded later, by the configuration management
  // keyboard: user part; e_key binary part
  // _keys_mapping: keyboard -> e_key ('z' and '8' can be used for LEFT key)
  // e_key -> keyboard (allow duplicated keys)

  _keys_mapping.insert({sf::Keyboard::Left,   e_key::LEFT});
  _keys_mapping.insert({sf::Keyboard::Right,  e_key::RIGHT});
  _keys_mapping.insert({sf::Keyboard::Up,     e_key::UP});
  _keys_mapping.insert({sf::Keyboard::Down,   e_key::DOWN});

  // These don't seem natural (but makes sense with a Workman layout)
  _keys_mapping.insert({sf::Keyboard::N,      e_key::LEFT });
  _keys_mapping.insert({sf::Keyboard::E,      e_key::UP   });
  _keys_mapping.insert({sf::Keyboard::O,      e_key::DOWN });
  _keys_mapping.insert({sf::Keyboard::I,      e_key::RIGHT});

  _keys_mapping.insert({sf::Keyboard::Space,  e_key::SELECTION});
  _keys_mapping.insert({sf::Keyboard::Escape, e_key::EXIT});

  // Accessible features whatever the state is
  _keys_mapping.insert({sf::Keyboard::Delete, e_key::SCREENSHOT});
  _keys_mapping.insert({sf::Keyboard::F3,     e_key::TOGGLE_PANEL});
  _keys_mapping.insert({sf::Keyboard::F12,    e_key::DUMP_MAP});
  _keys_mapping.insert({sf::Keyboard::F8,     e_key::QUICK_LOAD});
  _keys_mapping.insert({sf::Keyboard::F4,     e_key::QUICK_SAVE});

  // Editor
  _keys_mapping.insert({sf::Keyboard::T,         e_key::EDIT_TERRAIN_NEXT});
  _keys_mapping.insert({sf::Keyboard::U,         e_key::EDIT_UNIT_NEXT});
  _keys_mapping.insert({sf::Keyboard::BackSpace, e_key::EDIT_UNIT_DEL});


  // This event mapping is populated here but will then be read only
  // These are the mapping key (dissociated from the keyboard) -> event
  _events_mapping.insert({e_key::LEFT,         e_input::MOVE_LEFT   });
  _events_mapping.insert({e_key::RIGHT,        e_input::MOVE_RIGHT  });
  _events_mapping.insert({e_key::UP,           e_input::MOVE_UP     });
  _events_mapping.insert({e_key::DOWN,         e_input::MOVE_DOWN   });
  _events_mapping.insert({e_key::SELECTION,    e_input::SELECTION   });
  _events_mapping.insert({e_key::EXIT,         e_input::EXIT        });
  _events_mapping.insert({e_key::TOGGLE_PANEL, e_input::TOGGLE_PANEL});
  _events_mapping.insert({e_key::SCREENSHOT,   e_input::SCREENSHOT  });
  _events_mapping.insert({e_key::DUMP_MAP,     e_input::DUMP_MAP    });
  _events_mapping.insert({e_key::QUICK_LOAD,   e_input::QUICK_LOAD  });
  _events_mapping.insert({e_key::QUICK_SAVE,   e_input::QUICK_SAVE  });

  _events_mapping.insert({e_key::EDIT_TERRAIN_NEXT,
                          e_input::EDIT_TERRAIN_NEXT});
  _events_mapping.insert({e_key::EDIT_UNIT_NEXT, e_input::EDIT_UNIT_NEXT});
  _events_mapping.insert({e_key::EDIT_UNIT_DEL,  e_input::EDIT_UNIT_DEL});
}



void KeyManager::pushEvent(const sf::Keyboard::Key& key)
{
  // getting the logical key
  auto logical_key_it(_keys_mapping.find(key));
  if (logical_key_it == _keys_mapping.end())
  {
    return;
  }

  auto logical_key(logical_key_it->second);
  if (_replay && _replay->mode() == e_replay_mode::RECORD)
  {
    // Logging only 'useful' events
    _replay->storeKey(logical_key);
  }

  _active_inputs.push(_events_mapping[logical_key]);
}



void KeyManager::pushKey(const e_key& key)
{
  if (_replay && _replay->mode() == e_replay_mode::RECORD)
  {
    // Logging only 'useful' events
    _replay->storeKey(key);
  }

  _active_inputs.push(_events_mapping.at(key));
}



void KeyManager::pushKeyFromReplay(const e_key& key)
{
  _active_inputs.push(_events_mapping[key]);
}


e_input KeyManager::popEvent()
{
  return _active_inputs.pop();
}
