/**
 * \file
 * \brief Status templates implementation
 * \author Zermingore
 * \date October 19, 2019
 */

#include <game/Status.hh>
#include <context/State.hh>



namespace game {

/**
 * \brief Resume the current state (at the top of _states stack)
 * \note does *NOT* pop the stack
 */
template<typename... Attributes>
void Status::setStateAttributes(Attributes... attributes)
{
  _lock.lock();
  //assert(!_states.empty() && "_states stack is empty");

  _states.top().second->setAttributes(attributes...);
  _lock.unlock();
}


}
