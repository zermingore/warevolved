/**
 * \file
 * \date June 21, 2017
 * \author Zermingore
 * \brief InputsListener class definition
 */

#include <input/InputsListener.hh>

#include <chrono>
#include <future>

#include <context/State.hh>
#include <debug/Debug.hh>
#include <game/Map.hh>
#include <game/Battle.hh>
#include <game/Status.hh>
#include <game/Player.hh>
#include <interface/Cursor.hh>
#include <graphics/GraphicsEngine.hh>
#include <graphics/Properties.hh>
#include <input/EventManager.hh>
#include <input/EventsProcessor.hh>
#include <input/KeyManager.hh>
#include <input/ReplayManager.hh>
#include <tools/StringParser.hh>



void InputsListener::listen(bool replay,
                            const std::string& replay_filename,
                            const std::string& replay_header,
                            const std::atomic_bool& stop_events_listener)
{
  Debug::setThisThreadName("InputsListener");

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
    replay_manager->setReplayFile(replay_filename, replay_header);
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

      // Mouse
      if (event.type == sf::Event::MouseMoved)
      {
        // event.mouseMove.{x,y}: coordinates in px -> should never be negative
        if (event.mouseMove.x < 0 || event.mouseMove.y < 0)
        {
          WARNING("Negative mouse coordinates");
          break;
        }

        static int last_mouse_x = 0;
        static int last_mouse_y = 0;

        using p = graphics::Properties;
        const auto cell_width { static_cast<int> (p::cellWidth()) };
        const auto cell_height { static_cast<int> (p::cellHeight()) };

        // Avoid spamming cursor move
        if (   std::abs(last_mouse_x - event.mouseMove.x) < cell_width / 2
            && std::abs(last_mouse_y - event.mouseMove.y) < cell_height / 2)
        {
          break;
        }
        last_mouse_x = event.mouseMove.x;
        last_mouse_y = event.mouseMove.y;

        const auto grid_x { static_cast<int> (p::gridOffsetX()) };
        const auto grid_y { static_cast<int> (p::gridOffsetY()) };
        const Coords mouse {
           static_cast<size_t> ((event.mouseMove.x - grid_x) / cell_width),
           static_cast<size_t> ((event.mouseMove.y - grid_y) / cell_height) };

        static Coords mouse_old_cell = mouse;

        if (mouse.l < mouse_old_cell.l)
        {
          mouse_old_cell = mouse;
          KeyManager::pushKey(e_key::UP);
          break;
        }
        if (mouse.l > mouse_old_cell.l)
        {
          mouse_old_cell = mouse;
          KeyManager::pushKey(e_key::DOWN);
          break;
        }
        if (mouse.c < mouse_old_cell.c)
        {
          mouse_old_cell = mouse;
          KeyManager::pushKey(e_key::LEFT);
          break;
        }
        if (mouse.c > mouse_old_cell.c)
        {
          mouse_old_cell = mouse;
          KeyManager::pushKey(e_key::RIGHT);
          break;
        }

        break;
      }

      if (event.type == sf::Event::MouseButtonReleased)
      {
        KeyManager::pushKey(e_key::SELECTION);
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



void InputsListener::replay(const std::shared_ptr<ReplayManager>& replay_mgr)
{
  using namespace std::chrono;
  using dur_milli = duration<double, milliseconds::period>;

  // Read replay events, from the pre-filled replay events map
  auto events(replay_mgr->events());
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
