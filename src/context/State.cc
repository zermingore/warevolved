#include <context/State.hh>
#include <input/EventManager.hh>
#include <common/enums/states.hh>


State::State()
  : _evtMgr(std::make_shared<EventManager> ())
{
}
