#include <game/Game.hh>

#include <future>
#include <cassert>

#include <core/Context.hh>
#include <input/InputsListener.hh>
#include <graphics/GraphicsEngine.hh>
#include <game/Battle.hh>
#include <resources/ResourcesManager.hh>
#include <game/Status.hh>
#include <common/enums/states.hh>
#include <context/State.hh>


Game::Game()
{
  Context context(true);
}


void Game::run(bool replay)
{
  using namespace graphics; // function scope

  /// \todo main menu (pushState or the like)

  resources::ResourcesManager::initialize("resources.xml");

  auto battle(std::make_shared<Battle> ());
  game::Status::setBattle(battle);
  battle->initializeMap();

  auto inputs_listen(
    std::async(std::launch::async, InputsListener::listen, replay));

  game::Status::pushState(e_state::PLAYING);
  game::Status::currentState()->resume();

  // Game loop: processing events, updating display
  while (GraphicsEngine::windowIsOpen())
  {
    GraphicsEngine::drawScene(battle);
  }
}
