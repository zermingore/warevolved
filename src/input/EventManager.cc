#include <input/EventManager.hh>
#include <debug/Debug.hh>
#include <common/enums/states.hh>


bool EventManager::process(const e_input input)
{
  if (_callbacks.find(input) == _callbacks.end())
  {
    ERROR("callback not found for input", static_cast<int> (input));
    return false;
  }

  _callbacks[input]();
  return true;
}
