#include <input/KeyManager.hh>
#include <common/globals.hh>


KeyManager::KeyManager()
{
  for (unsigned int i = 0; i < nb_timer; ++i)
	_ready[i] = true;

  this->mapKeys();
}

KeyManager::~KeyManager() {
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

  // action keys
  _keys[selection_1] = sf::Keyboard::Space;
  _keys[selection_2] = sf::Keyboard::Return;
}

int KeyManager::getTime(e_timer function)
{
  return _clocks[function].getElapsedTime().asMilliseconds();
}

void KeyManager::setReady(e_timer index, bool state)
{
  _ready[index] = state;
}


bool KeyManager::ready(e_timer index)
{
  if (_clocks[index].getElapsedTime().asMilliseconds() > g_key_repeat_delay)
	this->restartTimer(index);

  return (_ready[index]);
}


void KeyManager::restartTimer(e_timer index)
{
  _clocks[index].restart();
  _ready[index] = true;
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


bool KeyManager::selection()
{
  return (sf::Keyboard::isKeyPressed(_keys[selection_1]) ||
		  sf::Keyboard::isKeyPressed(_keys[selection_2]));
}
