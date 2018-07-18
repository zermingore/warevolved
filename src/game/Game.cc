#include <game/Game.hh>

#include <future>
#include <cassert>

#include <tools/options/OptionsParser.hh>
#include <graphics/Context.hh>
#include <input/InputsListener.hh>
#include <graphics/GraphicsEngine.hh>
#include <game/Battle.hh>
#include <resources/ResourcesManager.hh>
#include <game/Status.hh>
#include <common/enums/states.hh>
#include <context/State.hh>

#include <debug/Debug.hh>

Game::Game(const OptionsParser& options_parser)
  : _optionsParser(options_parser)
  , _replayFiles(options_parser["replay-file"].arguments())
{
  graphics::Context context(options_parser.optionExists("fullscreen"));
  for (const auto arg: _replayFiles)
  {
    PRINTF("arg: ", arg);
  }
}


void Game::run()
{
  using namespace graphics; // function scope

  /// \todo main menu (pushState or the like)

  resources::ResourcesManager::initialize("resources.xml");

  auto battle(std::make_shared<Battle> ());
  game::Status::setBattle(battle);
  battle->initializeMap();

  auto inputs_listen(
    std::async(std::launch::async, InputsListener::listen, false, ""));

  game::Status::pushState(e_state::PLAYING);
  game::Status::currentState()->resume();

  // Drawing loop
  GraphicsEngine::drawScene(battle);
}
