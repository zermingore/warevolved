#include <common/Status.hh>
#include <input/InputProcessor.hh>
#include <graphics/GraphicsEngine.hh>
#include <common/State.hh>
#include <input/KeyManager.hh>


bool InputProcessor::process()
{
  sf::Event event;
  auto km = std::make_shared<KeyManager> ();
  while (graphics::GraphicsEngine::pollEvent(event))
  {
    // Close window: exit request
    if (event.type == sf::Event::Closed)
    {
      graphics::GraphicsEngine::closeWindow();
      return false;
    }

    km->populateEvents();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
      std::cout << "PRESSED" << std::endl;


    // if sf::Keyboard::isKeyPressed(sf::Keyboard::escape)...
    // we don't care of the event type for now


    // for (auto st: states)
    // {
    //   if (st->eventManager()->process(event))
    //     break;
    // }

    // call KeyManager to have a e_key from a sf::key
    // but we still need an e_event

    // key manager _events_mapping (not _keys_mapping)
    // auto ev = KeyManager[event.]
//    Status::currentState()->eventManager()->process(event);
  }

  return true;
}

//   if (_event.type == sf::Event::KeyReleased)
//     releasedKeys();


// void InputProcessor::processEvents()
// {
//   if (_km->exit() && _km->switchStatus(E_SWITCH_EXIT) == OFF)
//   {
//     Status::exitCurrentMode();
//     _km->setSwitchStatus(E_SWITCH_EXIT, ON);
//     graphics::GraphicsEngine::closeWindow();
//   }
// }
