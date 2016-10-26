#include <context/State.hh>
#include <input/EventManager.hh>


State::State()
  : _evtMgr(std::make_shared<EventManager> ())
{
}
