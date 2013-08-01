#include <game/Game.hh>
#include <graphics/GraphicEngine.hh>
#include <input/Event.hh>
#include <common/globals.hh>


Game::Game() :
  _event (NULL)
{
  // build map
  _map = new Map(8, 8);
  Player *player = new Player();
  Player *player2 = new Player();
  g_status->addPlayer(player);
  g_status->addPlayer(player2);
  g_status->setMap(_map);
  _map->init();
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
  while (WINDOW->isOpen() && _event->process())
  {
    graphics->drawScene();
    WINDOW->display(); // Update the window

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
