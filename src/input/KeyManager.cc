#include <input/KeyManager.hh>


KeyManager::KeyManager()
{
  this->mapKeys();
}

KeyManager::~KeyManager()
{
}

void KeyManager::mapKeys()
{
  // read configuration file to retrieve these values
  // use Settings Class
  _keys[move_up_1] = sf::Keyboard::Up;
  _keys[move_up_2] = sf::Keyboard::W;
  _keys[move_down_1] = sf::Keyboard::Down;
  _keys[move_down_2] = sf::Keyboard::S;
  _keys[move_left_1] = sf::Keyboard::Left;
  _keys[move_left_2] = sf::Keyboard::A;
  _keys[move_right_1] = sf::Keyboard::Right;
  _keys[move_right_2] = sf::Keyboard::D;
}

int KeyManager::getTimer(e_timer function)
{
  return _timers[function].getElapsedTime().asMilliseconds();
}


void KeyManager::restartTimer(e_timer index)
{
  _timers[index].restart();
}


bool KeyManager::up()
{
  return (sf::Keyboard::isKeyPressed(_keys[move_up_1]) ||
		  sf::Keyboard::isKeyPressed(_keys[move_up_2]));
}

bool KeyManager::down()
{
  return (sf::Keyboard::isKeyPressed(_keys[move_down_1]) ||
		  sf::Keyboard::isKeyPressed(_keys[move_down_2]));
}

bool KeyManager::left()
{
  return (sf::Keyboard::isKeyPressed(_keys[move_left_1]) ||
		  sf::Keyboard::isKeyPressed(_keys[move_left_2]));
}

bool KeyManager::right()
{
  return (sf::Keyboard::isKeyPressed(_keys[move_right_1]) ||
		  sf::Keyboard::isKeyPressed(_keys[move_right_2]));
}
