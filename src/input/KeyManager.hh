#ifndef KEYMANAGER_HH_
# define KEYMANAGER_HH_

# include <common/include.hh>
# include <common/constants.hh>

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
  //E_SWITCH_ACTION, // action menu (after moving a unit)

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
public:
  /** \brief Default Constructor
   */
  KeyManager();
  /** \brief Destructor
   */
  ~KeyManager();

  bool up();
  bool down();
  bool left();
  bool right();
  bool selection();
  bool exit();

  /** \brief Maps keyboard keys to function
   */
  void mapKeys();

  /** \brief timer value getter
   ** \param function Function associated to the the timer we're looking for
   ** \return Timer number index value (in ms)
   */
  int getTime(e_timer function);

  /** \brief switch getter
   ** \param index _switches index to retrieve
   ** \return switch status
   */
  bool getSwitchStatus(e_switch index);

  /** \brief switch getter
   ** \param s Switch to retrieve
   ** \return switch status
   */
  void setSwitchStatus(e_switch index, bool status);

  /** \brief returns true if the key matching index is ready
   ** \return true if the key matching index is ready
   **   false otherwise
   */
  bool ready(e_timer index);

  /** \brief notify a key as 'ready'
   **   meaning being considered as pressed again
   */
  void setReady(e_timer index, bool state);

  /** \brief restarts the clock \param index and sets _timers[index] to 0
   */
  void restartTimer(e_timer index);


private:
  sf::Keyboard::Key _keys[E_KEY_NB_KEYS]; ///< keys list
  sf::Clock _clocks[E_TIMER_NB_TIMERS]; ///< internals clocks
                                        ///< (to know if a key is ready)
  bool _ready[E_TIMER_NB_TIMERS]; ///< keys states
  bool _switches[E_SWITCH_NB_SWITCHES]; ///< switches states
};

#endif /* !KEYMANAGER_HH_ */
