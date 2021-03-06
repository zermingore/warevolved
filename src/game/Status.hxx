/**
 * \file
 * \date October 19, 2019
 * \author Zermingore
 * \brief Status templates implementation
 */

#ifndef STATUS_HXX_
# define STATUS_HXX_

# include <game/Status.hh>
# include <context/State.hh>


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


} // namespace game


#endif // STATUS_HXX_
