#include <game/Game.hh>
#include <graphics/GraphicsEngine.hh>
#include <input/EventManager.hh>
#include <game/applications/Battle.hh>
#include <input/KeyManager.hh>
#include <resources/ResourcesManager.hh>
#include <common/Status.hh>
#include <common/State.hh>
#include <input/InputProcessor.hh>

void Game::run()
{
  using namespace graphics; // function scope
  auto battle = std::make_shared<Battle> ();
  auto input_processor = std::make_shared<InputProcessor> ();

  resources::ResourcesManager::initialize("resources.xml");

  // Game loop: processing events, updating display
  // mode: playing
  // someone else need to process, not the event manager
  while (GraphicsEngine::windowIsOpen()
         && input_processor->process())
//       && Status::currentState()->eventManager()->execute())
  {
    GraphicsEngine::drawScene(battle);
  }
}
