#include <input/EventsProcessor.hh>

#include <debug/Debug.hh>
#include <common/Status.hh>
#include <context/State.hh>
#include <context/StateGlobal.hh>
#include <input/KeyManager.hh>
#include <input/EventManager.hh>
#include <input/KeyManager.hh>



[[ noreturn ]] void EventsProcessor::process()
{
  auto globalState { std::make_unique<StateGlobal> () };
  for (;;)
  {
    // process KeyManager events queue
    auto event(KeyManager::popEvent());
    if (   !Status::currentState()->eventManager()->process(event)
        && !globalState->eventManager()->process(event))
    {
      PRINTF("Event not processed");
    }
  }
}
