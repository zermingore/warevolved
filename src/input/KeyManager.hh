/*
 * input/keyManager.hh
 *
 *  Created on: April 17, 2013
 *      Author: Zermingore
 */

#ifndef KEYMANAGER_HH_
# define KEYMANAGER_HH_

# include <common/include.hh>
# include <common/constants.hh>
//# include <common/globals.hh>

/** \brief timer index list
 */
enum e_timer
{
  E_TIMER_MOVE_UP = 0,
  E_TIMER_MOVE_DOWN,
  E_TIMER_MOVE_LEFT,
  E_TIMER_MOVE_RIGHT,

  E_TIMER_NB_TIMERS
};


/** \brief switches (on /off) keys
 ** they don't allow key-repeating
 */
enum e_switch
{
  E_SWITCH_SELECTION = 0, // in-game selection menu

  E_SWITCH_MENUBAR,
  E_SWITCH_PANEL,

  E_SWITCH_EXIT, // exit request

  E_SWITCH_NB_SWITCHES
};


/** \brief Keys indexes
 ** allowing key repeating
 */
enum e_key
{
  // motion keys
  E_KEY_MOVE_UP_1 = 0,
  E_KEY_MOVE_UP_2,
  E_KEY_MOVE_DOWN_1,
  E_KEY_MOVE_DOWN_2,
  E_KEY_MOVE_LEFT_1,
  E_KEY_MOVE_LEFT_2,
  E_KEY_MOVE_RIGHT_1,
  E_KEY_MOVE_RIGHT_2,

  // action keys
  E_KEY_SELECTION_1,
  E_KEY_SELECTION_2,

  // menu keys
  E_KEY_MENUBAR_1,
  E_KEY_MENUBAR_2,
  E_KEY_PANEL_1,
  E_KEY_PANEL_2,

  // exit requests
  E_KEY_EXIT_1,
  E_KEY_EXIT_2,

  E_KEY_NB_KEYS
};


class KeyManager
{
/** \brief SFML key detection
 **   \return true if one of the two possible binding
 **     of a function has been triggered
 **   \return false otherwise
 **   \param feature key name auto expand _1 and _2 to this name
 */
# define PRESSED(x) sf::Keyboard::isKeyPressed(_keys[ x ##_1]) || \
    sf::Keyboard::isKeyPressed(_keys[ x ##_2])

public:
  /** \brief Default Constructor
   */
  KeyManager();

  inline bool up() { return (PRESSED(E_KEY_MOVE_UP)); }
  inline bool down() { return (PRESSED(E_KEY_MOVE_DOWN)); }
  inline bool left() { return (PRESSED(E_KEY_MOVE_LEFT)); }
  inline bool right() { return (PRESSED(E_KEY_MOVE_RIGHT)); }
  inline bool selection() { return (PRESSED(E_KEY_SELECTION)); }
  inline bool menubar() { return (PRESSED(E_KEY_MENUBAR)); }
  inline bool panel() { return (PRESSED(E_KEY_PANEL)); }
  inline bool exit() { return (PRESSED(E_KEY_EXIT)); }

  /** \brief Maps keyboard keys to function
   */
  void mapKeys();

  /** \brief timer value getter
   ** \param function Function associated to the the timer we're looking for
   ** \return Timer number index value (in ms)
   */
  inline int getTime(e_timer function)
  { return _clocks[function].getElapsedTime().asMilliseconds(); }

  /** \brief switch getter
   ** \param index _switches index to retrieve
   ** \return switch status
   */
  inline bool switchStatus(e_switch index) { return _switches[index]; }

  /** \brief switch getter
   ** \param s Switch to retrieve
   ** \return switch status
   */
  inline void setSwitchStatus(e_switch index, bool status)
  { _switches[index] = status; }

  /** \brief resets _switches status, if needed
   */
  void resetSwitches();

  /** \brief returns true if the key matching index is ready
   ** \return true if the key matching index is ready
   **   false otherwise
   */
  bool ready(e_timer index);

  /** \brief notify a key as 'ready'
   **   meaning being considered as pressed again
   */
  inline void setReady(e_timer index, bool state) { _ready[index] = state; }

  /** \brief restarts the clock \param index and sets _timers[index] to 0
   */
  void restartTimer(e_timer index);


private:
  sf::Keyboard::Key _keys[E_KEY_NB_KEYS]; ///< keys list
  sf::Clock _clocks[E_TIMER_NB_TIMERS]; ///< internals clocks (for key readiness)
  bool _ready[E_TIMER_NB_TIMERS]; ///< keys states
  bool _switches[E_SWITCH_NB_SWITCHES]; ///< switches states
};

#endif /* !KEYMANAGER_HH_ */
