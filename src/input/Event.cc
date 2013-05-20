#include <input/Event.hh>
#include <common/Status.hh>
#include <common/globals.hh>

Event::Event() {
}

Event::Event(KeyManager* km,
			 GraphicEngine* ge) :
  _km (km),
  _ge (ge)
{
  for (int i = 0; i < E_TIMER_NB_TIMERS; ++i)
  	_km->restartTimer(static_cast<e_timer>(i));

  g_settings->setKeyRepeatDelay(150);
}

Event::~Event() {
}


void Event::process()
{
  while (g_status->getWindow()->pollEvent(_event))
  {
	// Close window : exit
	if (_event.type == sf::Event::Closed)
	  g_status->getWindow()->close();
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	g_status->getWindow()->close(); // TODO call menu instead of quitting

  if (_event.type == sf::Event::KeyReleased)
  	this->releasedKeys();

  e_event_mode mode = g_status->getEventMode();
  if (mode >= E_EVENT_IN_GAME)
  {
	this->panel();
	if (g_status->getSelectionMode()) // mode == E_EVENT_MENU_SELECTION)
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
  if (_km->selection() && _km->getSwitchStatus(E_SWITCH_SELECTION) == OFF)
  {
	_km->setSwitchStatus(E_SWITCH_SELECTION, ON);
	g_status->setSelectionMode(false);
  }

  if (_km->up() && _km->ready(E_TIMER_MOVE_UP))
  {
	//_selectionMenu->incrementSelectedEntry();
	_ge->incrementSelectedEntry();
	_km->setReady(E_TIMER_MOVE_UP, false);
  }

  if (_km->down() && _km->ready(E_TIMER_MOVE_DOWN))
  {
	_ge->decrementSelectedEntry();
	_km->setReady(E_TIMER_MOVE_DOWN, false);
  }
}

void Event::game()
{
  if (_km->selection() && _km->getSwitchStatus(E_SWITCH_SELECTION) == OFF)
  {
	g_status->cellSelection();
	_km->setSwitchStatus(E_SWITCH_SELECTION, ON);
	g_status->setSelectionMode(true);
  }

  // ---------- Cursor Motion ---------- //
  if (_km->up() && _km->ready(E_TIMER_MOVE_UP))
  {
	g_status->getCursor()->moveUp();
	// the timer will not be ready until
	//   key_repeat_delay passed OR we release the key pressed
	_km->setReady(E_TIMER_MOVE_UP, false);
  }

  if (_km->down() && _km->ready(E_TIMER_MOVE_DOWN))
  {
	g_status->getCursor()->moveDown();
	_km->setReady(E_TIMER_MOVE_DOWN, false);
  }

  if (_km->left() && _km->ready(E_TIMER_MOVE_LEFT))
  {
	g_status->getCursor()->moveLeft();
	_km->setReady(E_TIMER_MOVE_LEFT, false);
  }

  if (_km->right() && _km->ready(E_TIMER_MOVE_RIGHT))
  {
	g_status->getCursor()->moveRight();
	_km->setReady(E_TIMER_MOVE_RIGHT, false);
  }
  // ----------------------------------- //
}


void Event::releasedKeys()
{
  // The timer we want to reset must not match a pressed key
  // (in case 2 keys are pressed simultaneously)

  if (!_km->up())
	_km->restartTimer(E_TIMER_MOVE_UP);

  if (!_km->down())
	_km->restartTimer(E_TIMER_MOVE_DOWN);

  if (!_km->left())
	_km->restartTimer(E_TIMER_MOVE_LEFT);

  if (!_km->right())
	_km->restartTimer(E_TIMER_MOVE_RIGHT);

  if (!_km->selection() && _km->getSwitchStatus(E_SWITCH_SELECTION) == ON)
	_km->setSwitchStatus(E_SWITCH_SELECTION, OFF);
}
