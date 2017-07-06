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
# include <chrono>

# include <SFML/Window/Event.hpp>
# include <SFML/System/Clock.hpp> /// \todo use std::clock instead
# include <SFML/Window/Keyboard.hpp>
# include <structures/ThreadSafeQueue.hh>


enum class e_input;


/**
 * \enum e_key
 * \brief Keys indexes allowing key repeating.
 */
enum class e_key
{
  // action keys
  SELECTION,

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
   * \param replay \true if we are in replay mode
   * \note if \param replay is \false the events will be logged
   */
  static void Initialize(bool replay);

  /**
   * \brief Append the givent key to the end of the replay file
   * \param key Key to log in the replay file
   * \return a list of events and their associated timestamps
   */
  static void replayStoreKey(const e_key& key);

  /**
   * \brief Push the event matching the given input into the events queue
   * \param input Input used to match the event to push in the queue
   */
  static void pushEvent(const sf::Keyboard::Key& key);

  /**
   * \brief Push a key as is in the fifo (which should be from the replay)
   * \param key key to push in the fifo
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

  /// events mapping
  static std::map<const e_key, const e_input> _events_mapping;

  /// current inputs (high level keys)
  static ThreadSafeQueue<e_input> _active_inputs;

  static bool _replay; ///< \false -> need to log every event

  static std::unique_ptr<std::ofstream> _replayFile; ///< Replay file

  ///< Creation time of the replay file
  static std::chrono::steady_clock::time_point _replayCreationTime;
};


#endif /* !INPUT_KEY_MANAGER_HH_ */
