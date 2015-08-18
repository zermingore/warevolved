#include <input/KeyManager.hh>
#include <common/Settings.hh>


KeyManager::KeyManager()
{
  for (auto i = 0; i < E_TIMER_NB_TIMERS; ++i)
    _ready[i] = true;

  for (auto i = 0; i < E_SWITCH_NB_SWITCHES; ++i)
	_switches[i] = false;

  mapKeys();
}


void KeyManager::mapKeys()
{
  // read configuration file to retrieve these values
  // use Settings Class
  _keys[E_KEY_MOVE_UP_1] = sf::Keyboard::Up;
  _keys[E_KEY_MOVE_UP_2] = sf::Keyboard::W;
  _keys[E_KEY_MOVE_DOWN_1] = sf::Keyboard::Down;
  _keys[E_KEY_MOVE_DOWN_2] = sf::Keyboard::S;
  _keys[E_KEY_MOVE_LEFT_1] = sf::Keyboard::Left;
  _keys[E_KEY_MOVE_LEFT_2] = sf::Keyboard::A;
  _keys[E_KEY_MOVE_RIGHT_1] = sf::Keyboard::Right;
  _keys[E_KEY_MOVE_RIGHT_2] = sf::Keyboard::D;

  // action keys
  _keys[E_KEY_SELECTION_1] = sf::Keyboard::Space;
  _keys[E_KEY_SELECTION_2] = sf::Keyboard::Return;

  // menu keys
  _keys[E_KEY_MENUBAR_1] = sf::Keyboard::F3;
  _keys[E_KEY_MENUBAR_2] = sf::Keyboard::F3;
  _keys[E_KEY_PANEL_1] = sf::Keyboard::F2;
  _keys[E_KEY_PANEL_2] = sf::Keyboard::F2;

  // exit request keys
  _keys[E_KEY_EXIT_1] = sf::Keyboard::Escape;
  _keys[E_KEY_EXIT_2] = sf::Keyboard::Escape;
}

bool KeyManager::ready(e_timer index)
{
  if (_clocks[index].getElapsedTime().asMilliseconds() > Settings::keyRepeatDelay())
    restartTimer(index);

  return (_ready[index]);
}


void KeyManager::restartTimer(e_timer index)
{
  _clocks[index].restart();
  _ready[index] = true;
}


void KeyManager::resetSwitches()
{
  if (!PRESSED(E_KEY_SELECTION))
    _switches[E_SWITCH_SELECTION] = OFF;

  if (!PRESSED(E_KEY_MENUBAR))
    _switches[E_SWITCH_MENUBAR] = OFF;

  if (!PRESSED(E_KEY_PANEL))
    _switches[E_SWITCH_PANEL] = OFF;

  if (!PRESSED(E_KEY_EXIT))
    _switches[E_SWITCH_EXIT] = OFF;
}
