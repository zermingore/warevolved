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
  sf::Clock timer;
  std::vector<sf::Int64> frame_generation;
# endif

  // Game loop
  while (g_status->getWindow()->isOpen())
  {
    _event->process(); // should be the first task of the game loop
    graphics->drawScene();

    // Update the window
    g_status->getWindow()->display();

#   ifdef DEBUG_PERFS
    g_status->setCurrentFPS(1000000 / timer.getElapsedTime().asMicroseconds());
    // storing all values, avoiding syscalls
    frame_generation.push_back(timer.getElapsedTime().asMicroseconds());
    timer.restart();
#   endif
  }


// finished the main loop, displaying performances
# ifdef DEBUG_PERFS
  for (unsigned int i = 0; i < frame_generation.size(); ++i)
  {
    std::cout << "frame generation: " << frame_generation[i]
              << "\tFPS: " << 1000000 / frame_generation[i]
              << std::endl;
  }
# endif


# ifdef DEBUG_LEAKS
  //delete km;
  //delete graphics;
# endif
}
