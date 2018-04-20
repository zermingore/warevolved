/**
 * \file
 * \date April 17, 2013
 * \author Zermingore
 */

#ifndef INPUT_KEY_MANAGER_HH_
# define INPUT_KEY_MANAGER_HH_

# include <map>
# include <set>
# include <string>
# include <memory>
# include <chrono>

# include <SFML/Window/Event.hpp>
# include <SFML/System/Clock.hpp> /// \todo use std::clock instead
# include <SFML/Window/Keyboard.hpp>
# include <structures/ThreadSafeQueue.hh>

class ReplayManager;
enum class e_input;


/**
 * \enum e_key
 * \brief Keys indexes allowing key repeating.
 */
enum class e_key
{
  // action keys
  SELECTION,

  // Global actions
  SCREENSHOT,

  // Interface keys
  TOGGLE_PANEL,

  // exit requests
  EXIT,

  UP,
  DOWN,
  LEFT,
  RIGHT,

  NB_KEYS
};


/**
 * \class KeyManager
 * \brief maps the raw input keys into events.
 *   It has a fifo filled by the \see InputsListener
 *   and read by the EventsProcessor.
 *   Logs the events if necessary (in non replay mode)
 */
class KeyManager
{
public:
  /**
   * \brief Initialize the mappings keyboard_inputs -> keys
   *   and keys -> high_level_inputs
   * \param replay true if we are in replay mode
   * \note If replay is false the events will be logged
   */
  static void Initialize(std::shared_ptr<ReplayManager> replay);

  /**
   * \brief Append the givent key to the end of the replay file
   * \param key Key to log in the replay file
   */
  static void replayStoreKey(const e_key& key);

  /**
   * \brief Push the event matching the given input into the events queue
   * \param key Key used to fetch the Event to push in the queue
   */
  static void pushEvent(const sf::Keyboard::Key& key);

  /**
   * \brief Push a key as is in the fifo (which should be from the replay)
   * \param key Key to push in the fifo
   */
  static void pushKeyFromReplay(const e_key& key);

  /**
   * \brief Retrieve the oldest event from the events queue
   * \return The poped event
   * \note Blocks until an event is found in the queue
   */
  static e_input popEvent();



private:
  /// Hardware / logical keys mapping
  static std::multimap<const sf::Keyboard::Key, const e_key> _keys_mapping;

  /// Events mapping
  static std::map<const e_key, const e_input> _events_mapping;

  /// Current inputs (high level keys)
  static ThreadSafeQueue<e_input> _active_inputs;

  /// Pointer on the replay manager to add keys to a replay being created
  static std::shared_ptr<ReplayManager> _replay;
};


#endif /* !INPUT_KEY_MANAGER_HH_ */
