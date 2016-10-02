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

  resources::ResourcesManager::initialize("resources.xml");

  // Game loop: processing events, updating display
  // mode: playing
  while (GraphicsEngine::windowIsOpen()
         && Status::currentState()->eventManager()->process())
  {
    GraphicsEngine::drawScene(battle);
  }
}
