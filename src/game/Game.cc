#include <game/Game.hh>
#include <graphics/GraphicEngine.hh>
#include <input/Event.hh>
#include <common/globals.hh>


Game::Game()
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
  g_status->setMap(_map);
  GraphicEngine* graphics = new GraphicEngine();
  KeyManager* km = new KeyManager();
  _event = new Event(km, graphics);

# ifdef DEBUG_PERFS
  g_status->getWindow()->setFramerateLimit(0);
  sf::Clock timer;
# endif

  // Game loop
  while (g_status->getWindow()->isOpen())
  {
	_event->process(); // should be the first task of the game loop
	graphics->drawScene();

	// Update the window
	g_status->getWindow()->display();

#   ifdef DEBUG_PERFS // TODO do not use syscalls
	g_status->setCurrentFPS(1000000 / timer.getElapsedTime().asMicroseconds());

	std::cout << "frame generation: " << timer.getElapsedTime().asMicroseconds()
			  << "\tFPS: " << g_status->getCurrentFPS()
			  << std::endl;
	timer.restart();
#   endif
  }

# ifdef DEBUG_LEAKS
  //delete km;
  //delete graphics;
//  delete status;
# endif
}
