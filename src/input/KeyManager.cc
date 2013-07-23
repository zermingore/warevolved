#include <input/KeyManager.hh>
#include <common/globals.hh>


KeyManager::KeyManager()
{
  for (unsigned int i = 0; i < E_TIMER_NB_TIMERS; ++i)
    _ready[i] = true;

  this->mapKeys();
}

KeyManager::~KeyManager() {
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

int KeyManager::getTime(e_timer function) {
  return _clocks[function].getElapsedTime().asMilliseconds();
}

bool KeyManager::getSwitchStatus(e_switch index) {
  return _switches[index];
}

void KeyManager::setSwitchStatus(e_switch index, bool status) {
  _switches[index] = status;
}

void KeyManager::setReady(e_timer index, bool state) {
  _ready[index] = state;
}

bool KeyManager::ready(e_timer index)
{
  if (_clocks[index].getElapsedTime().asMilliseconds() > g_settings->getKeyRepeatDelay())
    this->restartTimer(index);

  return (_ready[index]);
}


void KeyManager::restartTimer(e_timer index)
{
  _clocks[index].restart();
  _ready[index] = true;
}


bool KeyManager::up() {
  return (PRESSED(E_KEY_MOVE_UP));
}

bool KeyManager::down() {
  return (PRESSED(E_KEY_MOVE_DOWN));
}

bool KeyManager::left() {
  return (PRESSED(E_KEY_MOVE_LEFT));
}

bool KeyManager::right() {
  return (PRESSED(E_KEY_MOVE_RIGHT));
}

bool KeyManager::selection() {
  return (PRESSED(E_KEY_SELECTION));
}

bool KeyManager::exit() {
  return (PRESSED(E_KEY_EXIT));
}
