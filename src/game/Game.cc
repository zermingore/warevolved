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

  resources::ResourcesManager::initialize("resources.xml");

  auto battle(std::make_shared<Battle> ());
  Status::setBattle(battle);

  auto input_processor(std::make_shared<InputProcessor> ());
  Status::setInputProcessor(input_processor);

  Status::pushState(e_state::PLAYING);

  // Game loop: processing events, updating display
  while (GraphicsEngine::windowIsOpen() && input_processor->process()) {
    GraphicsEngine::drawScene(battle);
  }
}
