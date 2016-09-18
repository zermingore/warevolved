#include <input/EventManager.hh>
#include <common/enums/modes.hh>
#include <input/KeyManager.hh>
#include <common/Status.hh>
#include <common/Settings.hh>
#include <interface/Interface.hh>
#include <graphics/GraphicsEngine.hh>

#include <input/MapEventManager.hh>


EventManager::EventManager()
{
//  _km = std::make_shared<KeyManager> ();
//  for (auto i = 0; i < E_TIMER_NB_TIMERS; ++i)
//    _km->restartTimer(static_cast<e_timer> (i));

//  Settings::setKeyRepeatDelay(150);

//  std::shared_ptr<MapEventManager> m;
//  _managers.push_front(m);
}


//bool EventManager::execute(e_key key)
//{
////  if (_callbacks.find(key) == _callbacks.end())
////  {
////    DEBUG_PRINT("callback not found");
////    return false;
////  }

////  _callbacks[key]();
//  return true;
//}


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
