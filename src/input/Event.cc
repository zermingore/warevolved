#include <input/Event.hh>
#include <common/Status.hh>

int g_key_repeat_delay;

Event::Event() {
}

Event::Event(sf::RenderWindow* window,
			 KeyManager* km,
			 GraphicEngine* ge,
			 Status* status) :
  _window (window),
  _km (km),
  _ge (ge),
  _status (status)
{
  for (int i = 0; i < E_NB_TIMERS; ++i)
  	_km->restartTimer(static_cast<e_timer>(i));

  g_key_repeat_delay = 150;
}

Event::~Event() {
}


void Event::process()
{
  while (_window->pollEvent(_event))
  {
	// Close window : exit
	if (_event.type == sf::Event::Closed)
	  _window->close();
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	_window->close(); // TODO call menu instead of quitting

  if (_event.type == sf::Event::KeyReleased)
  	this->releasedKeys();

  e_event_mode mode = _status->getEventMode();
  if (mode >= E_EVENT_IN_GAME)
  {
	this->panel();
	if (_status->getSelectionMode()) // mode == E_EVENT_MENU_SELECTION)
	  this->menu();
	else
	  this->game();
  }
}


void Event::panel()
{

}


void Event::menu()
{
  if (_km->selection() && _km->getSwitchStatus(E_SELECTION) == OFF)
  {
	_km->setSwitchStatus(E_SELECTION, ON);
	_status->setSelectionMode(false);
  }
}

void Event::game()
{
  if (_km->selection() && _km->getSwitchStatus(E_SELECTION) == OFF)
  {
	_status->cellSelection();
	_km->setSwitchStatus(E_SELECTION, ON);
	_status->setSelectionMode(true);
  }

  // ---------- Cursor Motion ---------- //
  if (_km->up() && _km->ready(E_MOVE_UP))
  {
	_status->getCursor()->moveUp();
	// the timer will not be ready until
	//   g_key_repeat_delay passed OR we release the key pressed
	_km->setReady(E_MOVE_UP, false);
  }

  if (_km->down() && _km->ready(E_MOVE_DOWN))
  {
	_status->getCursor()->moveDown();
	_km->setReady(E_MOVE_DOWN, false);
  }

  if (_km->left() && _km->ready(E_MOVE_LEFT))
  {
	_status->getCursor()->moveLeft();
	_km->setReady(E_MOVE_LEFT, false);
  }

  if (_km->right() && _km->ready(E_MOVE_RIGHT))
  {
	_status->getCursor()->moveRight();
	_km->setReady(E_MOVE_RIGHT, false);
  }
  // ----------------------------------- //
}


void Event::releasedKeys()
{
  // The timer we want to reset must not match a pressed key
  // (in case 2 keys are pressed simultaneously)

  if (!_km->up())
	_km->restartTimer(E_MOVE_UP);

  if (!_km->down())
	_km->restartTimer(E_MOVE_DOWN);

  if (!_km->left())
	_km->restartTimer(E_MOVE_LEFT);

  if (!_km->right())
	_km->restartTimer(E_MOVE_RIGHT);

  if (!_km->selection() && _km->getSwitchStatus(E_SELECTION) == ON)
	_km->setSwitchStatus(E_SELECTION, OFF);
}
