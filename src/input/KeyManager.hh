/**
 * \file
 * \date April 17, 2013
 * \author Zermingore
 */

#ifndef INPUT_KEY_MANAGER_HH_
# define INPUT_KEY_MANAGER_HH_

# include <common/include.hh>

enum class e_input;


class InputKey
{
public:
  InputKey(e_input input) { _input = input; }


private:
  e_input _input;
};


/**
 * \brief timer index list
 */
enum e_timer
{
  E_TIMER_MOVE_UP = 0,
  E_TIMER_MOVE_DOWN,
  E_TIMER_MOVE_LEFT,
  E_TIMER_MOVE_RIGHT,

  E_TIMER_NB_TIMERS
};


/**
 * \brief switches keys. Do not allow key-repeatition (on /off).
 */
enum e_switch
{
  E_SWITCH_SELECTION = 0, // in-game selection menu

  E_SWITCH_MENUBAR,
  E_SWITCH_PANEL,

  E_SWITCH_EXIT, // exit request

  E_SWITCH_NB_SWITCHES
};


/**
 * \brief Keys indexes allowing key repeating.
 */
enum e_key
{
  // // motion keys -> events !
  // E_KEY_MOVE_UP_1 = 0,
  // E_KEY_MOVE_UP_2,
  // E_KEY_MOVE_DOWN_1,
  // E_KEY_MOVE_DOWN_2,
  // E_KEY_MOVE_LEFT_1,
  // E_KEY_MOVE_LEFT_2,
  // E_KEY_MOVE_RIGHT_1,
  // E_KEY_MOVE_RIGHT_2,

  // // action keys
  E_KEY_SELECTION_1,
  // E_KEY_SELECTION_2,

  // // exit requests
  E_KEY_EXIT_1,
  // E_KEY_EXIT_2,

  E_KEY_UP,
  E_KEY_DOWN,
  E_KEY_LEFT,
  E_KEY_RIGHT,


  E_KEY_NB_KEYS
};


/**
 * \class KeyManager
 * \brief maps the raw input keys into events.
 */
class KeyManager
{
  /**
   * \brief SFML key detection
   * \param feature key name auto expand _1 and _2 to this name
   * \return true if one of the two possible binding
   *   of a function has been triggered, false otherwise.
   */
# define PRESSED(x) true /*sf::Keyboard::isKeyPressed(_keys[ x ##_1]) || \
  sf::Keyboard::isKeyPressed(_keys[ x ##_2])*/

public:
  /// Default Constructor. Initializes the timers / switches
  KeyManager();

  void getEvent(sf::Keyboard::Key key);

  void populateEvents();

  /**
   * \brief returns the list of available and non blocked inputs
   */
  std::vector<e_input> activeInputs() { return _active_inputs; }


  /**
   * \brief Blocks every input, active or not
   * \param duration Time in ms during which one events will be ignored
   */
  void blockInputs(unsigned int duration = 100);



private:
  /**
   * \brief Returns a boolean to know if the inputs are available
   *
   * If they are not, they will be available in max _clock_events_freeze ms
   *   (unless a call to blockInputs is made)
   */
  bool eventsFreezed();


  //  std::pair<bool, sf::Keyboard::Key> _keys[E_KEY_NB_KEYS]; ///< keys list
  std::multimap<sf::Keyboard::Key, e_key> _keys_mapping; ///< key mapping
  std::map<sf::Keyboard::Key, e_input> _events_mapping; ///< events mapping
  std::vector<e_input> _active_inputs; ///< current inputs (high level keys)
  sf::Clock _clocks[E_TIMER_NB_TIMERS]; ///< internals clocks (for key readiness)
  bool _ready[E_TIMER_NB_TIMERS]; ///< keys states
  bool _switches[E_SWITCH_NB_SWITCHES]; ///< switches states

  sf::Clock _clock_events_freeze; ///< clock to manage events freezing
  int _events_freeze_duration;    ///< duration to deactivate events
};


#endif /* !INPUT_KEY_MANAGER_HH_ */
