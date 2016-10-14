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

# include <iostream>

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
   * \brief Constructor. Fetch Cursor coordinates.
   * \param state State state value.
   */
  explicit State(e_state &state);

  /**
   * \brief _state getter
   * \return _state value
   */
  e_state currentState() { return _currentState; }

  // return specific State components
  // returns menu, ...
  virtual std::vector<int> getAttrList() {
    std::cout << "[IMPLEMENTATION ERROR] State "
              << "Illegal call to moterclass getAttrList()"
              << std::endl;

    return std::vector<int> ();
  }

  /**
   * \brief event manager getter
   * \return _eventManager
   */
  std::shared_ptr<EventManager> eventManager() { return _eventManager; }


private:
  e_state _currentState;         ///< State's state

  std::shared_ptr<EventManager> _eventManager; ///< State related events
};

#endif /* !STATE_HH_ */
