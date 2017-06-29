/**
 * \file
 * \date April 17, 2013
 * \author Zermingore
 */

#ifndef INPUT_KEY_MANAGER_HH_
# define INPUT_KEY_MANAGER_HH_

# include <map>
# include <set>

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
 */
class KeyManager
{
public:
  /**
   * \brief Initialize the mappings keys -> keyboard_inputs
   * and keys -> high_level_inputs
   */
  static void Initialize();


  /**
   * \brief Push the event matching the given input into the events queue
   * \param input Input used to match the event to push in the queue
   */
  static void pushEvent(const sf::Keyboard::Key& key);


  /**
   * \brief Retrieve the oldest event from the events queue
   * \return The poped event
   * \note Blocks until an event is found in the queue
   */
  static e_input popEvent();



private:
  /**
   * \brief Returns a boolean to know if the inputs are available
   *
   * If they are not, they will be available in max _clock_events_freeze ms
   *   (unless a call to blockInputs is made)
   */
  static bool eventsFreezed();

  /// Hardware / logical keys mapping
  static std::multimap<const sf::Keyboard::Key, const e_key> _keys_mapping;

  /// events mapping
  static std::map<const e_key, const e_input> _events_mapping;

  /// current inputs (high level keys)
  static ThreadSafeQueue<e_input> _active_inputs;

  static sf::Clock _clock_events_freeze; ///< clock to manage events freezing
  static size_t _events_freeze_duration; ///< duration to deactivate events
};


#endif /* !INPUT_KEY_MANAGER_HH_ */
