/*
 * common/State.hh
 *
 *  Created on: July 24, 2013
 *      Author: Zermingore
 */

#ifndef STATE_HH_
# define STATE_HH_

# include <memory>
# include <common/using.hh>
# include <common/enums/modes.hh>
# include <common/structures/Vector.hh>

class Menu;
class EventManager;

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
   * \brief Constructor
   *
   * Fetch Cursor coordinates.
   *
   * \param mode State mode value.
   */
  explicit State(e_mode &mode);

  /**
   * \brief Constructor
   *
   * Fetch Cursor coordinates.
   *
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
   * \brief _cursorCoords getters
   * \return _cursorCoords value
   */
//  Coords cursorCoords() { return _cursorCoords; }

  /**
   * \brief event manager getter
   * \return _eventManager
   */
  std::shared_ptr<EventManager> eventManager() { return _eventManager; }


private:
  e_mode _currentMode;         ///< State's mode
  std::shared_ptr<Menu> _menu; ///< menu state to save

  std::shared_ptr<EventManager> _eventManager; ///< State related events
//  Coords _cursorCoords; ///< Cursor coordinates when the mode was activated
};

#endif /* !STATE_HH_ */
