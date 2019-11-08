#include <input/InputsListener.hh>

#include <chrono>
#include <future>

#include <common/enums/input.hh>
#include <context/State.hh>
#include <debug/Debug.hh>
#include <game/Status.hh>
#include <graphics/GraphicsEngine.hh>
#include <input/EventManager.hh>
#include <input/EventsProcessor.hh>
#include <input/KeyManager.hh>
#include <input/ReplayManager.hh>
#include <tools/StringParser.hh>



void InputsListener::listen(bool replay,
                            const std::string& replay_filename,
                            const std::atomic_bool& stop_events_listener)
{
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
  auto inputs = std::async(std::launch::async, EventsProcessor::process);

  // Listen for events until the window close event is found
  while (!stop_events_listener)
  {
    // Listen to input, convert them into events and push them in the fifo
    sf::Event event{};
    while (graphics::GraphicsEngine::pollEvent(event))
    {
      // Close window: exit request
      if (event.type == sf::Event::Closed)
      {
        // Simulating a keyboard exit in order to terminate the input thread
        game::Status::clearStates();
        KeyManager::pushEvent(sf::Keyboard::Escape);
        break;
      }

      // Resize event
      if (event.type == sf::Event::Resized)
      {
        graphics::GraphicsEngine::resizeWindow(event.size.width,
                                               event.size.height);
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



void InputsListener::replay(const std::shared_ptr<ReplayManager>& replay_manager)
{
  using namespace std::chrono;
  using dur_milli = duration<double, milliseconds::period>;

  // Read replay events, from the pre-filled replay events map
  auto events(replay_manager->events());
  auto start(steady_clock::now());
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
