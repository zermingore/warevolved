#include <context/State.hh>

#include <input/EventManager.hh>
#include <interface/InterfaceElement.hh>



State::State()
  : _evtMgr(std::make_shared<EventManager> ())
{
}


void State::draw()
{
  for (auto it: _interfaceElements) {
    it->draw();
  }
}
