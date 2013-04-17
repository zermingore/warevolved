#include <input/KeyManager.hh>


KeyManager::KeyManager()
{
  _motion_direction[0] = sf::Keyboard::Up;
  _motion_direction[1] = sf::Keyboard::W;
  _motion_direction[2] = sf::Keyboard::Down;
  _motion_direction[3] = sf::Keyboard::S;
  _motion_direction[4] = sf::Keyboard::Left;
  _motion_direction[5] = sf::Keyboard::A;
  _motion_direction[6] = sf::Keyboard::Right;
  _motion_direction[7] = sf::Keyboard::D;

  //_motion_timers[0] = new sf::Time(0);
}

KeyManager::~KeyManager()
{
}


bool KeyManager::up()
{
  return (sf::Keyboard::isKeyPressed(_motion_direction[0]) ||
		  sf::Keyboard::isKeyPressed(_motion_direction[1]));
}

bool KeyManager::down()
{
  return (sf::Keyboard::isKeyPressed(_motion_direction[2]) ||
		  sf::Keyboard::isKeyPressed(_motion_direction[3]));
}

bool KeyManager::left()
{
  return (sf::Keyboard::isKeyPressed(_motion_direction[4]) ||
		  sf::Keyboard::isKeyPressed(_motion_direction[5]));
}

bool KeyManager::right()
{
  return (sf::Keyboard::isKeyPressed(_motion_direction[6]) ||
		  sf::Keyboard::isKeyPressed(_motion_direction[7]));
}
