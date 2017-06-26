#include <input/EventsProcessor.hh>

#include <common/Status.hh>
#include <context/State.hh>
#include <input/KeyManager.hh>
#include <input/EventManager.hh>
#include <input/KeyManager.hh>


std::shared_ptr<KeyManager> EventsProcessor::_km;


void EventsProcessor::process()
{
  for (;;)
  {
    // process _km->popEvent()
    // if (Status::currentState()->eventManager()->process(_km->popEvent()))
    // {
    //   PRINTF("Processed:", (int) i, "in current state", Status::currentState());
    // }
  }
}
