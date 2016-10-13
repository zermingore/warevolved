#include <game/Game.hh>
#include <graphics/GraphicsEngine.hh>
#include <game/applications/Battle.hh>
#include <resources/ResourcesManager.hh>
#include <input/InputProcessor.hh>


void Game::run()
{
  using namespace graphics; // function scope
  auto battle = std::make_shared<Battle> ();
  auto input_processor = std::make_shared<InputProcessor> ();

  resources::ResourcesManager::initialize("resources.xml");

  // Game loop: processing events, updating display
  // state: playing
  while (GraphicsEngine::windowIsOpen() && input_processor->process())
  {
    GraphicsEngine::drawScene(battle);
  }
}
