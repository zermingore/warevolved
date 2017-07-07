#include <input/EventsProcessor.hh>

#include <debug/Debug.hh>
#include <common/Status.hh>
#include <context/State.hh>
#include <input/KeyManager.hh>
#include <input/EventManager.hh>
#include <input/KeyManager.hh>



[[ noreturn ]] void EventsProcessor::process()
{
  for (;;)
  {
    // process KeyManager events queue
    if (!Status::currentState()->eventManager()->process(KeyManager::popEvent()))
    {
      PRINTF("Event not processed");
    }
  }
}