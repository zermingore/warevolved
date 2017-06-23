#include <input/InputsListener.hh>

#include <iostream>

#include <debug/EventsLogger.hh>
#include <common/Status.hh>
#include <graphics/GraphicsEngine.hh>
#include <context/State.hh>
#include <input/KeyManager.hh>
#include <common/enums/input.hh>
#include <input/EventManager.hh>



InputsListener::InputsListener(bool replay)
  : _km(std::make_shared<KeyManager> ())
  , _replay(replay)
{
  // if (_replay)
  //   _replayEvents = debug::EventsLogger::fetchEventsReplay();
  // else
  //   debug::EventsLogger::initialize("LOG_EVENTS");

  _creationTime = std::chrono::steady_clock::now();
}


void InputsListener::pollEvents()
{
  for (;;)
  {
    // Listen to input, convert them into events and push them in the fifo
    sf::Event event;
    while (graphics::GraphicsEngine::pollEvent(event))
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

      // Loosy: for all register event, push the matching ones
      _km->populateEvents();
    }
  }
}
