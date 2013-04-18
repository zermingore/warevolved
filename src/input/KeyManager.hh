#ifndef KEYMANAGER_HH_
# define KEYMANAGER_HH_

# include <common/include.hh>

// timer index
enum e_timer
{
  move_up = 0,
  move_down,
  move_left,
  move_right,
  nb_timer
};


// keys index
enum e_keys
{
  // motion keys
  move_up_1 = 0,
  move_up_2,
  move_down_1,
  move_down_2,
  move_left_1,
  move_left_2,
  move_right_1,
  move_right_2,

  // action keys
  selection_1,
  selection_2,

  // interface keys
  menubar,
  panel,

  nb_keys
};



class KeyManager
{
public:
  KeyManager();
  ~KeyManager();

  bool up();
  bool down();
  bool left();
  bool right();

  bool selection();

  void mapKeys();

  /// returns the timer number index value (in ms)
  int getTime(e_timer function);

  bool ready(e_timer index);

  void setReady(e_timer index, bool state);

  /// restarts the clock \param index and sets _timers[index] to 0
  void restartTimer(e_timer index);


private:
  sf::Keyboard::Key _keys[nb_keys];
  sf::Clock _clocks[8];
  bool _ready[8];
};

#endif /* !KEYMANAGER_HH_ */
