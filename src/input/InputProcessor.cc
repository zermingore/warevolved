#include <common/Status.hh>
#include <input/InputProcessor.hh>
#include <graphics/GraphicsEngine.hh>
#include <context/State.hh>
#include <input/KeyManager.hh>
#include <common/enums/input.hh>
#include <debug/EventsLogger.hh>
#include <input/EventManager.hh>



InputProcessor::InputProcessor(bool replay)
  : _km(std::make_shared<KeyManager> ())
  , _replay(replay)
{
  if (_replay)
    _replayEvents = debug::EventsLogger::fetchEventsReplay();
  else
    debug::EventsLogger::initialize("LOG_EVENTS");

  _creationTime = std::chrono::steady_clock::now();
}


bool InputProcessor::processEvent(sf::Event event)
{
  // Close window: exit request
  if (event.type == sf::Event::Closed)
  {
    graphics::GraphicsEngine::closeWindow();
    return false;
  }

  // skipping any non-relevant event
  if (event.type != sf::Event::KeyPressed)
  {
    return true;
  }

  _km->populateEvents();
  for (const auto& i: _km->activeInputs())
  {
    if (Status::currentState()->eventManager()->process(i))
    {
      if (!_replay)
      {
        debug::EventsLogger::logProcessedEvent(i);
      }
      // PRINTF("processed:", (int) i,
      //        "in current state", Status::currentState());
    }
  }

  return true;
}


bool InputProcessor::process()
{
  if (_replay)
  {
    replay();
    _replay = false; // read events from keyboard after playing the replay
  }

  sf::Event event;
  while (graphics::GraphicsEngine::pollEvent(event))
  {
    debug::EventsLogger::log(event);

    if (!processEvent(event))
    {
      return false;
    }
  }

  return true;
}


bool InputProcessor::replay()
{
  // time elapsed since the beginning
  auto time_elapsed = std::chrono::duration_cast<std::chrono::microseconds> (
    std::chrono::steady_clock::now() - _creationTime);

  // Check if it's too late to play events
  if (_replayEvents.cend()->first > time_elapsed)
  {
    return false;
  }

  // for each event in the replay, wait for the associated timestamp
  for (auto it: _replayEvents)
  {
    // \todo busy waiting (replaying events must be in its own thread anyway)
    while (it.first > time_elapsed)
    {
      time_elapsed = std::chrono::duration_cast<std::chrono::microseconds> (
        std::chrono::steady_clock::now() - _creationTime);
    }

    Status::currentState()->eventManager()->process(static_cast<e_input> (it.second));

    std::cout << "played event after: " << time_elapsed.count() / 1000000l << std::endl;
  }

  return false;
}
