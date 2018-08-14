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



Game::Game(const OptionsParser& options_parser)
  : _optionsParser(options_parser)
{
  if (options_parser["replay"])
  {
    _replay = true;
  }
  if (const auto& opt = options_parser["replay-file"])
  {
    _replayFiles = opt.value().arguments();
  }

  graphics::Context context(options_parser.optionExists("fullscreen"));
}


void Game::run()
{
  using namespace graphics; // function scope

  /// \todo main menu (pushState or the like)

  resources::ResourcesManager::initialize("resources.xml");

  auto battle(std::make_shared<Battle> ());
  game::Status::setBattle(battle);
  battle->initializeMap();

  std::string replay_file = "events_log";
  if (_replayFiles.size())
  {
    replay_file = _replayFiles[0];
  }

  auto inputs = std::async(
    std::launch::async, InputsListener::listen, _replay, replay_file);

  game::Status::pushState(e_state::PLAYING);
  game::Status::currentState()->resume();

  // Drawing loop
  GraphicsEngine::drawScene(battle);
}
