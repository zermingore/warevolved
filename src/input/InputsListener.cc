#include <input/InputsListener.hh>

#include <future>
#include <chrono>

#include <debug/Debug.hh>
#include <debug/EventsLogger.hh>
#include <common/Status.hh>
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
  }
  else
  {
    replay_manager->setMode(e_replay_mode::RECORD);
    replay_manager->setReplayFile(replay_filename);
  }

  KeyManager::Initialize(replay_manager);

  // Launch the events processor in its own thread
  std::thread(EventsProcessor::process).detach();

  std::thread(InputsListener::replay, replay_manager).detach();

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
  auto current_time(std::chrono::steady_clock::now());

  // Read replay events, from the pre-filled replay events map
  auto events(replay_manager->events());
  auto start(std::chrono::steady_clock::now());
  for (const auto& logged_event: events)
  {
    // Wait for the event recorded time to push it in the fifo
    duration<double, std::milli> event_time(logged_event.first);
    for (;;)
    {
      auto time_now = steady_clock::now();

      duration<double, std::chrono::milliseconds::period> time_elapsed =
        duration_cast<duration<double, std::milli>> (time_now - start);

      if (time_elapsed.count() > event_time.count())
      {
        break;
      }

      // std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    KeyManager::pushKeyFromReplay(static_cast<e_key> (logged_event.second));
  }

  NOTICE("End reading replay file");
}
