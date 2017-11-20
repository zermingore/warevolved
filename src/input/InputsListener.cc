#include <input/InputsListener.hh>

#include <future>
#include <chrono>

#include <debug/Debug.hh>
#include <debug/EventsLogger.hh>
#include <game/Status.hh>
#include <graphics/GraphicsEngine.hh>
#include <context/State.hh>
#include <input/KeyManager.hh>
#include <common/enums/input.hh>
#include <input/EventManager.hh>
#include <input/EventsProcessor.hh>
#include <input/ReplayManager.hh>
#include <tools/StringParser.hh>



void InputsListener::listen(bool replay)
{
  auto replay_filename("test_log");
  // Initialize the replay mode as required (Read XOr Write)

  auto replay_manager = std::make_shared<ReplayManager> ();
  if (replay)
  {
    replay_manager->setMode(e_replay_mode::READ);
    replay_manager->prepareReplayKeys(replay_filename);
    std::thread(InputsListener::replay, replay_manager).detach();
  }
  else
  {
    replay_manager->setMode(e_replay_mode::RECORD);
    replay_manager->setReplayFile(replay_filename);
  }

  KeyManager::Initialize(replay_manager);

  // Launch the events processor in its own thread
  std::thread(EventsProcessor::process).detach();

  // Listen for events until the window close event is found
  for (;;)
  {
    // Listen to input, convert them into events and push them in the fifo
    sf::Event event;
    while (graphics::GraphicsEngine::waitEvent(event))
    {
      // Close window: exit request
      if (event.type == sf::Event::Closed)
      {
        graphics::GraphicsEngine::closeWindow();
        return;
      }

      // Skipping any non-relevant event
      if (event.type != sf::Event::KeyPressed)
      {
        continue;
      }

      // Push e_key matching the sf::Event
      KeyManager::pushEvent(event.key.code);
    }
  }
}



void InputsListener::replay(std::shared_ptr<ReplayManager> replay_manager)
{
  using namespace std::chrono;
  using dur_milli = duration<double, milliseconds::period>;
  auto current_time(steady_clock::now());

  // Read replay events, from the pre-filled replay events map
  auto events(replay_manager->events());
  auto start(steady_clock::now());
  dur_milli time_elapsed;
  for (const auto& [ timestamp, key ] : events)
  {
    // Wait for the event recorded time to push it in the fifo
    std::this_thread::sleep_for(
      dur_milli (timestamp)
      - duration_cast<dur_milli> (steady_clock::now() - start));

    KeyManager::pushKeyFromReplay(static_cast<e_key> (key));
  }

  NOTICE("End reading replay file");
}
