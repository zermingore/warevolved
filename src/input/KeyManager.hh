#ifndef KEYMANAGER_HH_
# define KEYMANAGER_HH_

# include <common/include.hh>

class KeyManager
{
public:
  KeyManager();
  ~KeyManager();

  virtual bool up();
  virtual bool down();
  virtual bool left();
  virtual bool right();

  sf::Clock _motion_timers[4];

private:
  sf::Keyboard::Key _motion_direction[8];
};

#endif /* !KEYMANAGER_HH_ */
