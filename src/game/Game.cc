#include <game/Game.hh>
#include <graphics/GraphicsEngine.hh>
#include <game/applications/Battle.hh>
#include <resources/ResourcesManager.hh>
#include <input/InputProcessor.hh>
#include <common/Status.hh>
#include <common/enums/states.hh>
#include <input/KeyManager.hh>


void Game::run()
{
  using namespace graphics; // function scope
  auto battle = std::make_shared<Battle> ();
  Status::setBattle(battle);

   // broken design (will need to access map, interface, resolution, ...)
  auto input_processor = std::make_shared<InputProcessor> ();

  resources::ResourcesManager::initialize("resources.xml");
  Status::pushState(e_state::PLAYING);

  // Game loop: processing events, updating display
  // state: playing
  while (GraphicsEngine::windowIsOpen() && input_processor->process())
  {
    GraphicsEngine::drawScene(battle);
  }
}
