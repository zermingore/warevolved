#include <input/Event.hh>
#include <tools/Cursor.hh>


int g_key_repeat_delay;

Event::Event()
{
}

Event::Event(sf::RenderWindow* window, KeyManager* km, Cursor* cursor)
{
  _window = window;
  _km = km;
  _cursor = cursor;

  // resetting all timers // TODO FIXME
  for (int i = 0; i < nb_timer; ++i)
  	_km->restartTimer((e_timer) i);

  g_key_repeat_delay = 150;
}

Event::~Event()
{
}


/* cd need to use callbacks */
void Event::process()
{
  while (_window->pollEvent(_event))
  {
	// Close window : exit
	if (_event.type == sf::Event::Closed)
	{
	  _window->close();
	}
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	_window->close(); // TODO call menu

  if (_event.type == sf::Event::KeyReleased)
  	this->resetTimer();

  this->game();
}


void Event::game()
{
  // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
  // 	GameEngine::selectCell();

  // ---------- Cursor Motion ---------- //
  if (_km->up() && _km->getTimer(move_up) > g_key_repeat_delay)
  {
	_km->restartTimer(move_up);
	_cursor->moveUp();
  }

  if (_km->down() && _km->getTimer(move_down) > g_key_repeat_delay)
  {
	_km->restartTimer(move_down);
	_cursor->moveDown();
  }

  if (_km->left() && _km->getTimer(move_left) > g_key_repeat_delay)
  {
	_km->restartTimer(move_left);
	_cursor->moveLeft();
  }

  if (_km->right() && _km->getTimer(move_right) > g_key_repeat_delay)
  {
	_km->restartTimer(move_right);
	_cursor->moveRight();
  }
  // ----------------------------------- //
}


void Event::resetTimer()
{
  _km->restartTimer(move_up);
}
