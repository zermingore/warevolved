#include <core/Game.hh>
#include <core/GraphicEngine.hh>
#include <tools/Cursor.hh>
#include <input/Event.hh>

unsigned int g_gridSizeX;
unsigned int g_gridSizeY;


Game::Game()
{
  std::cerr << "Must specify a window" << std::endl;
}

Game::Game(sf::RenderWindow* window)
{
  _window = window;
}

Game::~Game()
{
}


int Game::run()
{
  _cursor = new Cursor();
  GraphicEngine* graphics = new GraphicEngine(_window, _cursor);

  KeyManager* k = new KeyManager();
  _event = new Event(_window, k, _cursor);

  // Start the game loop
  while (_window->isOpen())
  {
	_event->process(); // should be the first task of the game loop

	graphics->drawGrid(5, 5);
	g_gridSizeX = 5;
	g_gridSizeY = 5;

	// Update the window
	_window->display();
  }

  return 0;
}
