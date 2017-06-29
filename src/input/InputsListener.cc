#include <input/InputsListener.hh>

#include <future>

#include <debug/EventsLogger.hh>
#include <common/Status.hh>
#include <graphics/GraphicsEngine.hh>
#include <context/State.hh>
#include <input/KeyManager.hh>
#include <common/enums/input.hh>
#include <input/EventManager.hh>
#include <input/EventsProcessor.hh>



void InputsListener::listen()
{
  KeyManager::Initialize();

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
