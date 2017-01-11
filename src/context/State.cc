#include <context/State.hh>
#include <input/EventManager.hh>
#include <common/enums/states.hh>
#include <interface/InterfaceElement.hh>
// #include <graphics/GraphicsEngine.hh>


State::State()
  : _evtMgr(std::make_shared<EventManager> ())
{
}


void State::draw()
{
  for (auto it: _interfaceElements) {
    it->draw();
    // graphics::GraphicsEngine::draw(it);
  }
}
