#include <input/Inputprocessor.hh>



boot Inputprocessor::process()
{
  sf::Event event;
  while (graphics::GraphicsEngine::pollEvent(event))
  {
    // Close window: exit request
    if (_event.type == sf::Event::Closed)
    {
      graphics::GraphicsEngine::closeWindow();
      return false;
    }

    // for (auto st: states)
    // {
    //   if (st->eventManager()->process(event))
    //     break;
    // }

    Status::currentMode()->eventManager()->process(event)
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
