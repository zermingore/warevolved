/**
 * \file
 * \date July 24, 2013
 * \author Zermingore
 */

#ifndef STATE_HH_
# define STATE_HH_


# include <memory>
# include <common/using.hh>
# include <common/structures/Vector.hh>

class Menu;
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
   * \brief Constructor. Fetch Cursor coordinates.
   * \param state State state value.
   * \param menu menu state to save.
   */
  State(e_state state, std::shared_ptr<Menu> menu);

  /**
   * \brief _state getter
   * \return _state value
   */
  e_state currentState() { return _currentState; }

  /**
   * \brief _menu getter
   * \return _menu a pointer over current menu
   */
  std::shared_ptr<Menu> menu() { return _menu; }

  /**
   * \brief event manager getter
   * \return _eventManager
   */
  std::shared_ptr<EventManager> eventManager() { return _eventManager; }


private:
  e_state _currentState;         ///< State's state
  std::shared_ptr<Menu> _menu; ///< menu state to save

  std::shared_ptr<EventManager> _eventManager; ///< State related events
};

#endif /* !STATE_HH_ */
