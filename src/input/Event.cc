#include <input/Event.hh>
#include <tools/Cursor.hh>


int g_key_repeat_delay;


Event::Event(sf::RenderWindow* window, KeyManager* km, Cursor* cursor)
{
  _window = window;
  _km = km;
  _cursor = cursor;

  g_key_repeat_delay = 500;
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
  if (_km->up()
	  && _km->_motion_timers[0].getElapsedTime().asMilliseconds() > g_key_repeat_delay)
  {
	std::cout << "blah" << std::endl;
	_km->_motion_timers[0].restart();
	_cursor->moveUp();
  }

  if (_km->down() && _km->_motion_timers[1].getElapsedTime().asMilliseconds() > g_key_repeat_delay)
	_cursor->moveDown();


  if (_km->left() && _km->_motion_timers[2].getElapsedTime().asMilliseconds() > g_key_repeat_delay)
	_cursor->moveLeft();

  if (_km->right() && _km->_motion_timers[3].getElapsedTime().asMilliseconds() > g_key_repeat_delay)
	_cursor->moveRight();
  // ----------------------------------- //


  if ((_km->up()) || (_km->down()) || (_km->left()) || (_km->right()))
	std::cout << "olol" << _km->_motion_timers[0].getElapsedTime().asMilliseconds() << std::endl;
}


void Event::resetTimer()
{
  _km->_motion_timers[0].restart();
}
