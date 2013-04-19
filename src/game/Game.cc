#include <game/Game.hh>
#include <core/GraphicEngine.hh>
#include <game/Cursor.hh>
#include <input/Event.hh>


Game::Game()
{
  std::cerr << "Must specify a window" << std::endl;
}

Game::Game(sf::RenderWindow* window) :
  _window (window)
{
  _map = new Map(8, 8);
}

Game::~Game()
{
  delete _map;
  delete _cursor;
  delete _event;
}


int Game::run()
{
  _cursor = new Cursor(_map->getNbColumns(), _map->getNbLines());
  GraphicEngine* graphics = new GraphicEngine(_window, _map, _cursor);

  KeyManager* k = new KeyManager();
  _event = new Event(_window, k, _cursor);

  // Start the game loop
  while (_window->isOpen())
  {
	_event->process(); // should be the first task of the game loop

	graphics->drawScene();

	// Update the window
	_window->display();
  }

# ifdef DEBUG_LEAKS
  delete k;
  delete graphics;
# endif

  return 0;
}
