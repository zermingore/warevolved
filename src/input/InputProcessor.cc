#include <common/Status.hh>
#include <input/InputProcessor.hh>
#include <graphics/GraphicsEngine.hh>
#include <context/State.hh>
#include <input/KeyManager.hh>
#include <common/enums/input.hh>



InputProcessor::InputProcessor()
  : _km(std::make_shared<KeyManager> ())
{
}

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

    _km->populateEvents();

    auto inputs(_km->activeInputs());
    for (const auto& i: inputs)
    {
      // special return value -> pop State ?
      if (Status::currentState()->eventManager()->process(i))
        std::cout << '+' << std::flush;
      else
        std::cout << '.' << std::flush;
    }
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
