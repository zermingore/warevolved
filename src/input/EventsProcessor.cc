/**
 * \file
 * \date June 22, 2017
 * \author Zermingore
 * \brief EventsProcessor class definition
 */

#include <input/EventsProcessor.hh>

#include <context/State.hh>
#include <context/StateGlobal.hh>
#include <debug/Debug.hh>
#include <game/Status.hh>
#include <input/EventManager.hh>
#include <input/KeyManager.hh>
#include <input/KeyManager.hh>


std::mutex EventsProcessor::_lock;
std::condition_variable EventsProcessor::_cv_new_frame;



void EventsProcessor::process()
{
  Debug::setThisThreadName("EventsProcessor");

  auto globalState { std::make_unique<StateGlobal> () };
  for (;;)
  {
    // Wait to access an event
    auto input(KeyManager::popEvent());

    // Waiting for the new frame, signaled by the Graphics Engine
    std::unique_lock<std::mutex> lock(_lock);
    _cv_new_frame.wait(lock);

    // process KeyManager events queue
    if (   !game::Status::processInput(input)
        && !globalState->eventManager()->process(input))
    {
      PRINTF("Event not processed");
    }
  }
}



void EventsProcessor::notifyFrame()
{
  _cv_new_frame.notify_one();
}
