/**
 * \file
 * \date July 24, 2013
 * \author Zermingore
 */

#ifndef STATE_HH_
# define STATE_HH_

# include <memory>
# include <vector>
# include <common/using.hh>
# include <common/structures/Vector.hh>

class EventManager;

enum class e_state;


/**
 * \class State
 * \brief Records a current state.
 *
 * Stores a state, which is composed of:
 *   a cursor position
 *   a state: \enum state index
 *   an event manager
 */
class State
{
public:
  /**
   * \brief Default constructor. Instantiates the EventManager
   */
  State();

  /**
   * \brief _state getter
   * \return _state value
   */
  e_state currentState() { return _currentState; }

  // return specific State components
  // returns menu, ...
  virtual std::vector<int> getAttrList() = 0;

  /**
   * \brief event manager getter
   * \return _eventManager
   */
  std::shared_ptr<EventManager> eventManager() { return _evtMgr; }


protected:
  e_state _currentState; ///< State's state
  std::shared_ptr<EventManager> _evtMgr; ///< State related events
};

#endif /* !STATE_HH_ */
