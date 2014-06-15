#include <game/Game.hh>
#include <graphics/GraphicEngine.hh>
#include <input/Event.hh>
#include <common/globals.hh>
#include <game/applications/Battle.hh>

Game::Game() :
  _event (nullptr)
{
}

void Game::run()
{
  std::shared_ptr<GraphicEngine> graphics(new GraphicEngine());
  std::shared_ptr<KeyManager> km(new KeyManager());
  _event.reset(new Event(km, graphics));

# ifdef DEBUG_PERFS
  sf::Clock timer;
  std::vector<sf::Int64> frame_generation;
# endif

  Battle b; // launch a new Battle
  graphics->initRoom();

  // Game loop
  while (g_window->isOpen() && _event->process())
  {
    graphics->drawScene();
    g_window->display(); // Update the window

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
}
