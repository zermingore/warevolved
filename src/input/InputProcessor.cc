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
      if (Status::currentState()->eventManager()->process(i))
        std::cout << '+';
      else
        std::cout << '.';
    }
    std::cout << std::endl;
  }

  return true;
}
