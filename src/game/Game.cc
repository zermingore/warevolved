#include <game/Game.hh>

#include <future>

#include <input/InputsListener.hh>
#include <graphics/GraphicsEngine.hh>
#include <game/Battle.hh>
#include <resources/ResourcesManager.hh>
#include <common/Status.hh>
#include <common/enums/states.hh>
#include <context/State.hh>



void Game::run(bool replay)
{
  using namespace graphics; // function scope

  resources::ResourcesManager::initialize("resources.xml");

  auto battle(std::make_shared<Battle> ());
  Status::setBattle(battle);
  battle->initializeMap();

  // auto input_processor(std::make_shared<InputProcessor> (replay));
  // Status::setInputProcessor(input_processor);

  std::future<void> inputs_listener = std::async(InputsListener::listen);

  Status::pushState(e_state::PLAYING);
  Status::currentState()->resume();

  /// \todo launch the InputsListener thread

  // Game loop: processing events, updating display
  while (GraphicsEngine::windowIsOpen()) {
    GraphicsEngine::drawScene(battle);
  }
}
