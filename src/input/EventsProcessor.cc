#include <input/EventsProcessor.hh>

#include <debug/Debug.hh>
#include <game/Status.hh>
#include <context/State.hh>
#include <context/StateGlobal.hh>
#include <input/KeyManager.hh>
#include <input/EventManager.hh>
#include <input/KeyManager.hh>


std::mutex EventsProcessor::_lock;
std::condition_variable EventsProcessor::_cv_new_frame;




void EventsProcessor::process()
{
  auto globalState { std::make_unique<StateGlobal> () };
  for (;;)
  {
    // Wait to access an event
    auto event(KeyManager::popEvent()); /// \todo if exit event -> exit

    // Waiting for the new frame, signaled by the Graphics Engine
    std::unique_lock<std::mutex> lock(_lock);
    _cv_new_frame.wait(lock);

    // process KeyManager events queue
    if (   !game::Status::currentState()->eventManager()->process(event)
        && !globalState->eventManager()->process(event))
    {
      PRINTF("Event not processed");
    }
  }
}



void EventsProcessor::notifyFrame()
{
  std::unique_lock<std::mutex> lock(_lock);
  _cv_new_frame.notify_one();
}
