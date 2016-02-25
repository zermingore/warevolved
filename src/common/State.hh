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

enum class e_mode;


/**
 * \class State
 * \brief Records a current state.
 *
 * Stores a state, which is composed of:
 *   a cursor position
 *   a mode: \enum state index
 *   an event manager
 */
class State
{
public:
  /**
   * \brief Constructor. Fetch Cursor coordinates.
   * \param mode State mode value.
   */
  explicit State(e_mode &mode);

  /**
   * \brief Constructor. Fetch Cursor coordinates.
   * \param mode State mode value.
   * \param menu menu state to save.
   */
  State(e_mode mode, std::shared_ptr<Menu> menu);

  /**
   * \brief _mode getter
   * \return _mode value
   */
  e_mode currentMode() { return _currentMode; }

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
  e_mode _currentMode;         ///< State's mode
  std::shared_ptr<Menu> _menu; ///< menu state to save

  std::shared_ptr<EventManager> _eventManager; ///< State related events
};

#endif /* !STATE_HH_ */
