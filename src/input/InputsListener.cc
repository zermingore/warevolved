#include <input/InputsListener.hh>

#include <debug/EventsLogger.hh>
#include <common/Status.hh>
#include <graphics/GraphicsEngine.hh>
#include <context/State.hh>
#include <input/KeyManager.hh>
#include <common/enums/input.hh>
#include <input/EventManager.hh>


std::shared_ptr<KeyManager> InputsListener::_km;


void InputsListener::listen()
{
  // Initialize the KeyManager
  _km = std::make_shared<KeyManager> ();

  // Listen for events until the window close event is found
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
