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
#include <tools/StringParser.hh>

// static members definition
std::vector<std::pair<std::chrono::duration<double>, int>>
  InputsListener::_replayEvents;



void InputsListener::getReplayKeys(const std::string& filename)
{
  NOTICE("Parsing replay", filename);

  char line[256];
  std::ifstream stream(filename, std::ios_base::in);
  while (stream.getline(line, 256))
  {
    // getting the input events only from the log
    auto entry(StringParser::split(line, " "));
    if (entry.size() != 2) // not the expected format: timestamp e_key
    {
      WARNING("Skipping line:", line);
      continue;
    }

    auto ts = std::chrono::nanoseconds{ atol(entry.front().c_str()) };
    auto key(entry[1]);
    _replayEvents.push_back({ ts, atoi(key.c_str()) });
    std::cout << "input: @" << ts.count()
              << ": " << _replayEvents.back().second << std::endl;
  }
}


void InputsListener::listen(bool replay)
{
  auto replay_filename("test_log");
  // Initialize the replay mode as required (Read XOr Write)
  if (!replay)
  {
    debug::EventsLogger::initialize(replay_filename);
  }
  else
  {
    getReplayKeys(replay_filename);
  }

  KeyManager::Initialize(replay);

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



void InputsListener::replay()
{
  using namespace std::chrono;
  auto current_time(std::chrono::steady_clock::now());

  // Read replay events, from the pre-filled replay events map
  for (const auto& logged_event: _replayEvents)
  {
    // Wait for the event recorded time to push it in the fifo
    std::chrono::duration<double, std::milli> wait_time(logged_event.first);
    // std::chrono::duration<double, std::milli> duration_start(current_time);


    auto start(std::chrono::steady_clock::now());
    for (;;)
    {
      duration<double, std::milli> duration_time_point_ms =
        duration_cast<duration<double>> (steady_clock::now() - start);

      // std::cout << "elapsed: " << duration_time_point_ms.count() - ms.count() << std::endl;
      if (duration_time_point_ms.count() > wait_time.count())
      {
        break;
      }
      // std::this_thread::sleep_for(std::chrono::millisecond(1));
    }

    PRINTF("pushing event ");
    KeyManager::pushKeyFromReplay(static_cast<e_key> (logged_event.second));
  }

  NOTICE("End reading replay file");
}
