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
  move_up_1 = 0,
  move_up_2,
  move_down_1,
  move_down_2,
  move_left_1,
  move_left_2,
  move_right_1,
  move_right_2,
  nb_keys
};



class KeyManager
{
public:
  KeyManager();
  ~KeyManager();

  virtual bool up();
  virtual bool down();
  virtual bool left();
  virtual bool right();

  void mapKeys();

  /// returns the timer number index value (in ms)
  int getTimer(e_timer function);
  void restartTimer(e_timer index);


private:
  sf::Keyboard::Key _keys[64];
  sf::Clock _timers[8];
};

#endif /* !KEYMANAGER_HH_ */
