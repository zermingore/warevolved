#include <common/Status.hh>
#include <input/InputProcessor.hh>
#include <graphics/GraphicsEngine.hh>
#include <common/State.hh>

bool InputProcessor::process()
{
  sf::Event event;
  while (graphics::GraphicsEngine::pollEvent(event))
  {
    // Close window: exit request
    if (event.type == sf::Event::Closed)
    {
      graphics::GraphicsEngine::closeWindow();
      return false;
    }

    // we don't care of the event type for now


    // for (auto st: states)
    // {
    //   if (st->eventManager()->process(event))
    //     break;
    // }

    // call KeyManager to have a e_key from a sf::key
    // but we still need an e_event
    // Status::currentState()->eventManager()->process(event)
  }

  return true;
}





// bool InputProcessor::process()
// {
//   while (graphics::GraphicsEngine::pollEvent(_event))
//   {
//     // Close window: exit request
//     if (_event.type == sf::Event::Closed)
//     {
//       graphics::GraphicsEngine::closeWindow();
//       return false;
//     }
//   }

//   if (_event.type == sf::Event::KeyReleased)
//     releasedKeys();

//   // trying to consume the event for every active EventManager
// //  for (const auto& event: _km->)
// //  {
// //    for (const auto& manager: _managers)
// //    {
// //      if (_managers.process())
// //      {
// //        events.erase(event);
// //        break;
// //      }
// //    }
// //  }

//   return true;
// }


// void InputProcessor::processEvents()
// {
//   if (_km->exit() && _km->switchStatus(E_SWITCH_EXIT) == OFF)
//   {
//     Status::exitCurrentMode();
//     _km->setSwitchStatus(E_SWITCH_EXIT, ON);
//     graphics::GraphicsEngine::closeWindow();
//   }
// }
