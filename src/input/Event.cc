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
  for (int i = 0; i < nb_timer; ++i)
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
  	this->resetTimer();

  this->game();
}


void Event::game()
{
  if (_km->selection())
  {
	if (!_km->ready(selection))
	  return;

	_status->cellSelection();
	// the timer will not be ready until
	//   g_key_repeat_delay passed OR we release the key pressed
	_km->setReady(selection, false);
  }

  // ---------- Cursor Motion ---------- //
  if (_km->up())
  {
	if (!_km->ready(move_up))
	  return;

	_status->getCursor()->moveUp();
	_km->setReady(move_up, false);
  }

  if (_km->down())
  {
	if (!_km->ready(move_down))
	  return;

	_status->getCursor()->moveDown();
	_km->setReady(move_down, false);
  }

  if (_km->left())
  {
	if (!_km->ready(move_left))
	  return;

	_status->getCursor()->moveLeft();
	_km->setReady(move_left, false);
  }

  if (_km->right())
  {
	if (!_km->ready(move_right))
	  return;

	_status->getCursor()->moveRight();
	_km->setReady(move_right, false);
  }
  // ----------------------------------- //
}


void Event::resetTimer()
{
  // The timer we want to reset must not match a pressed key
  // (in case 2 keys are pressed simultaneously)

  if (!_km->up())
	_km->restartTimer(move_up);

  if (!_km->down())
	_km->restartTimer(move_down);

  if (!_km->left())
	_km->restartTimer(move_left);

  if (!_km->right())
	_km->restartTimer(move_right);

  if (!_km->selection())
	_km->restartTimer(selection);
}
