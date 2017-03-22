#include <common/Status.hh>
#include <input/InputProcessor.hh>
#include <graphics/GraphicsEngine.hh>
#include <context/State.hh>
#include <input/KeyManager.hh>
#include <common/enums/input.hh>
#include <debug/EventsLogger.hh>



InputProcessor::InputProcessor()
  : _km(std::make_shared<KeyManager> ())
{
  EventsLogger::initialize("LOG_EVENTS");
}


bool InputProcessor::process()
{
  sf::Event event;
  while (graphics::GraphicsEngine::pollEvent(event))
  {
    EventsLogger::log(event);


    // Close window: exit request
    if (event.type == sf::Event::Closed)
    {
      graphics::GraphicsEngine::closeWindow();
      return false;
    }

    // skipping any non-relevant event
    if (event.type != sf::Event::KeyPressed)
    {
      continue;
    }

    _km->populateEvents();
    for (const auto& i: _km->activeInputs())
    {
      if (Status::currentState()->eventManager()->process(i))
      {
        EventsLogger::logProcessedEvent(i);
        // PRINTF("processed:", (int) i,
        //        "in current state", Status::currentState());
      }
    }
  }

  return true;
}
