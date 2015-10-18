#include <game/Game.hh>
#include <graphics/GraphicsEngine.hh>
#include <input/EventManager.hh>
#include <game/applications/Battle.hh>
#include <input/KeyManager.hh>
#include <resources/ResourcesManager.hh>
#include <common/Status.hh>
#include <common/State.hh>


void Game::run()
{
  using namespace graphics; // function scope
  auto battle = std::make_shared<Battle> ();

# ifdef DEBUG_PERFS
  sf::Clock timer;
  std::vector<sf::Int64> frame_generation;
# endif

  resources::ResourcesManager::initialize("resources.xml");
  // GraphicsEngine::initRoom();

  // Game loop
  while (GraphicsEngine::windowIsOpen() &&
         Status::currentState()->eventManager()->process())
  {
    GraphicsEngine::drawScene(battle->map());

#   ifdef DEBUG_PERFS
    GraphicsEngine::setCurrentFPS(1000000 / timer.getElapsedTime().asMicroseconds());
    // storing all values, avoiding syscalls
    frame_generation.push_back(timer.getElapsedTime().asMicroseconds());
    timer.restart();
#   endif
  }

  // finished the main loop, displaying performances
# ifdef DEBUG_PERFS
  for (auto i: frame_generation)
    PRINTF("frame generation:", i, "\tFPS:", 1000000 / i);
# endif
}
