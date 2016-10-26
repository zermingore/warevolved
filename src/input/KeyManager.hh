/**
 * \file
 * \date April 17, 2013
 * \author Zermingore
 */

#ifndef KEYMANAGER_HH_
# define KEYMANAGER_HH_

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

  /// Returns a e_key from a sf::key
  // e_key getKey(sf::Keyboard::Key key) { return _keys_mapping[key]; }


  /**
   * \brief timer value getter
   * \param function Function associated to the the timer we're looking for
   * \return Timer number index value (in ms)
   */
  int getTime(e_timer function) {
    return _clocks[function].getElapsedTime().asMilliseconds();
  }

  /**
   * \brief switch getter
   * \param index _switches index to retrieve
   * \return switch status
   */
  bool switchStatus(e_switch index) { return _switches[index]; }

  /**
   * \brief switch getter
   * \param index _switches index to retrieve
   * \param status switch status
   */
  void setSwitchStatus(e_switch index, bool status) {
    _switches[index] = status;
  }

  /**
   * \brief resets _switches status, if needed
   */
  void resetSwitches();

  /**
   * \brief returns true if the key matching index is ready
   * \return true if the key matching index is ready
   *   false otherwise
   */
  bool ready(e_timer index);

  /**
   * \brief notify a key as 'ready': considerable as pressed again.
   */
  void setReady(e_timer index, bool state) { _ready[index] = state; }

  /**
   * \brief restarts the clock.
   * \param index and sets _timers[index] to 0.
   */
  void restartTimer(e_timer index);

  /// sets the boolean of each considered key
  void setkeysStatus();

  void getEvent(sf::Keyboard::Key key);

  void populateEvents();

  bool isActive(e_input e);

  std::vector<e_input> activeInputs() { return _active_inputs; }

private:
  //  std::pair<bool, sf::Keyboard::Key> _keys[E_KEY_NB_KEYS]; ///< keys list
  std::multimap<sf::Keyboard::Key, e_key> _keys_mapping; ///< key mapping
  std::map<sf::Keyboard::Key, e_input> _events_mapping; ///< events mapping
  std::vector<e_input> _active_inputs; ///< current inputs (high level keys)
  sf::Clock _clocks[E_TIMER_NB_TIMERS]; ///< internals clocks (for key readiness)
  bool _ready[E_TIMER_NB_TIMERS]; ///< keys states
  bool _switches[E_SWITCH_NB_SWITCHES]; ///< switches states
};


#endif /* !KEYMANAGER_HH_ */
