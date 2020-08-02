/**
 * \file
 * \date April 17, 2013
 * \author Zermingore
 * \brief EventManager class definition
 */

#include <common/enums/states.hh>
#include <debug/Debug.hh>
#include <input/EventManager.hh>


bool EventManager::process(const e_input input)
{
  if (_callbacks.find(input) == _callbacks.end())
  {
    ERROR("Callback not found for input", static_cast<int> (input));
    return false;
  }

  _callbacks[input]();
  return true;
}
