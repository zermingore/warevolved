#include <common/Status.hh>
#include <input/InputProcessor.hh>
#include <graphics/GraphicsEngine.hh>
#include <context/State.hh>
#include <input/KeyManager.hh>
#include <common/enums/input.hh>


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

    auto inputs(km->activeInputs());
    for (const auto& i: inputs)
    {
      // special return value -> pop State ?
      if (Status::currentState()->eventManager()->process(i))
        std::cout << '+' << std::flush;
      else
        std::cout << '.' << std::flush;
    }

    // for every eventManager em
    //   for every watched event e
    //     if (keyManager::isActive(event))
    //       em->process(e)

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
//     Status::exitCurrentState();
//     _km->setSwitchStatus(E_SWITCH_EXIT, ON);
//     graphics::GraphicsEngine::closeWindow();
//   }
// }
