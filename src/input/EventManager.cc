#include <input/EventManager.hh>
#include <common/enums/modes.hh>
#include <input/KeyManager.hh>
#include <common/Status.hh>
#include <common/Settings.hh>
#include <interface/Interface.hh>
#include <graphics/GraphicsEngine.hh>


EventManager::EventManager()
{
//  _km = std::make_shared<KeyManager> ();
//  for (auto i = 0; i < E_TIMER_NB_TIMERS; ++i)
//    _km->restartTimer(static_cast<e_timer> (i));

//  Settings::setKeyRepeatDelay(150);
}


bool EventManager::execute(e_input input)
{
  std::cout << "IMPLEM: execute shd not be called" << std::endl;

 if (_callbacks.find(input) == _callbacks.end())
 {
   DEBUG_PRINT("callback not found");
   return false;
 }

 // key Vs event
 _callbacks[input]();
 return true;
}


bool EventManager::process(e_input input)
{
 if (_callbacks.find(input) == _callbacks.end())
 {
   std::cout << "callback not found for input "
             << static_cast<int> (input)
             << std::endl;
   return false;
 }

 _callbacks[input]();
 return true;
}

void EventManager::releasedKeys()
{
  // The timer we want to reset must not match a pressed key
  // (in case 2 keys are pressed simultaneously)

//  if (!_km->up())
//    _km->restartTimer(E_TIMER_MOVE_UP);

//  if (!_km->down())
//    _km->restartTimer(E_TIMER_MOVE_DOWN);

//  if (!_km->left())
//    _km->restartTimer(E_TIMER_MOVE_LEFT);

//  if (!_km->right())
//    _km->restartTimer(E_TIMER_MOVE_RIGHT);

//  _km->resetSwitches();
}
