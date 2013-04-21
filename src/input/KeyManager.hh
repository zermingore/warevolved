#ifndef KEYMANAGER_HH_
# define KEYMANAGER_HH_

# include <common/include.hh>
# include <common/constants.hh>

/** \brief timer index list
 */
enum e_timer
{
  E_MOVE_UP = 0,
  E_MOVE_DOWN,
  E_MOVE_LEFT,
  E_MOVE_RIGHT,

  E_NB_TIMERS
};


/** \brief switches (on /off) keys
 ** they don't allow key-repeating
 */
enum e_switch
{
  E_SELECTION = 0,

  E_NB_SWITCHES
};


// keys index
enum e_key
{
  // motion keys
  E_MOVE_UP_1 = 0,
  E_MOVE_UP_2,
  E_MOVE_DOWN_1,
  E_MOVE_DOWN_2,
  E_MOVE_LEFT_1,
  E_MOVE_LEFT_2,
  E_MOVE_RIGHT_1,
  E_MOVE_RIGHT_2,

  // action keys
  E_SELECTION_1,
  E_SELECTION_2,

  // interface keys
  E_MENUBAR,
  E_PANEL,

  E_NB_KEYS
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

  bool ready(e_timer index);

  void setReady(e_timer index, bool state);

  /** \brief restarts the clock \param index and sets _timers[index] to 0
   */
  void restartTimer(e_timer index);


private:
  sf::Keyboard::Key _keys[E_NB_KEYS];
  sf::Clock _clocks[E_NB_TIMERS];
  bool _ready[E_NB_TIMERS];
  bool _switches[E_NB_SWITCHES];
};

#endif /* !KEYMANAGER_HH_ */
