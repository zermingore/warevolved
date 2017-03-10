/**
 * \file
 * \date April 17, 2013
 * \author Zermingore
 */

#ifndef INPUT_KEY_MANAGER_HH_
# define INPUT_KEY_MANAGER_HH_

# include <common/include.hh>

enum class e_input;


/**
 * \enum e_key
 * \brief Keys indexes allowing key repeating.
 */
enum class e_key
{
  // // motion keys -> events !
  // MOVE_UP_1 = 0,
  // MOVE_UP_2,
  // MOVE_DOWN_1,
  // MOVE_DOWN_2,
  // MOVE_LEFT_1,
  // MOVE_LEFT_2,
  // MOVE_RIGHT_1,
  // MOVE_RIGHT_2,

  // // action keys
  SELECTION_1,
  // SELECTION_2,

  // // exit requests
  EXIT_1,
  // EXIT_2,

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
  /// Default Constructor. Maps the keyboard input to keys
  KeyManager();

  /**
   * \brief Populates the _active_inputs events list
   */
  void populateEvents();

  /**
   * \brief returns the list of available and non blocked inputs
   */
  auto activeInputs() { return _active_inputs; }


  /**
   * \brief Blocks every input, active or not
   * \param duration Time in ms during which one events will be ignored
   */
  void blockInputs(const unsigned int duration = 100);



private:
  /**
   * \brief Returns a boolean to know if the inputs are available
   *
   * If they are not, they will be available in max _clock_events_freeze ms
   *   (unless a call to blockInputs is made)
   */
  bool eventsFreezed();


  std::multimap<sf::Keyboard::Key, e_key> _keys_mapping; ///< key mapping
  std::map<sf::Keyboard::Key, e_input> _events_mapping;  ///< events mapping
  std::vector<e_input> _active_inputs; ///< current inputs (high level keys)

  sf::Clock _clock_events_freeze; ///< clock to manage events freezing
  int _events_freeze_duration;    ///< duration to deactivate events
};


#endif /* !INPUT_KEY_MANAGER_HH_ */
