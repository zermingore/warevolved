/**
 * \file
 * \date April 15, 2013
 * \author Zermingore
 * \brief Game class definition
 */

#include <game/Game.hh>

#include <future>

#include <config/Settings.hh>
#include <context/State.hh>
#include <debug/Debug.hh>
#include <game/Battle.hh>
#include <game/Status.hh>
#include <graphics/Context.hh>
#include <graphics/GraphicsEngine.hh>
#include <input/InputsListener.hh>
#include <resources/ResourcesManager.hh>
#include <tools/options/OptionsParser.hh>
#include <tools/Random.hh>



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

  auto battle(std::make_shared<Battle> (_optionsParser));
  game::Status::setBattle(battle);
  battle->initializeMap();

  std::string replay_file = "events_log";
  if (!_replayFiles.empty())
  {
    replay_file = _replayFiles[0];
  }

  std::stringstream replay_header;
  replay_header << "# version " << Settings::versionString() << '\n';
  if (_optionsParser.optionExists("load-map"))
  {
    replay_header << "# Loaded map file: "
                  << _optionsParser["load-map"].value().arguments()[0] << '\n';
  }
  replay_header << "# Random seed: " << std::to_string(Random::seed()) << '\n';

  std::atomic_bool stop_events_listener{false};
  auto inputs = std::async(
    std::launch::async,
    InputsListener::listen,
    _replay,
    replay_file,
    replay_header.str(),
    std::ref(stop_events_listener)
  );

  Debug::setThisThreadName("game");

  if (_optionsParser["edit-map"])
  {
    game::Status::pushState(e_state::EDIT_MAP);
  }
  else
  {
    game::Status::pushState(e_state::PLAYING);
  }
  game::Status::resumeState();

  GraphicsEngine::drawScene(battle); // Drawing loop

  // Exit request reached
  stop_events_listener = true;
  WARNING("Quitting War Evolved");
}
