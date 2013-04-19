#include <game/Game.hh>
#include <graphics/GraphicEngine.hh>
#include <input/Event.hh>


Game::Game() {
  std::cerr << "Must specify a window" << std::endl;
}

Game::Game(sf::RenderWindow* window) :
  _window (window)
{
  // build map
  _map = new Map(8, 8);
}

Game::~Game()
{
  delete _map;
  delete _event;
}


void Game::run()
{
  Status* status = new Status(_map);
  GraphicEngine* graphics = new GraphicEngine(_window, _map, status);
  KeyManager* km = new KeyManager();
  _event = new Event(_window, km, graphics, status);

  // Start the game loop
  while (_window->isOpen())
  {
	_event->process(); // should be the first task of the game loop
	graphics->drawScene();

	// Update the window
	_window->display();
  }

# ifdef DEBUG_LEAKS
  delete km;
  delete graphics;
  delete status;
# endif
}
