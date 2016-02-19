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
 * \brief state class
 ** stores a state, which is composed of
 **   a cursor position
 **   a mode: \enum state index
 **   an event manager
 */
class State
{
public:
  /** Constructor
   ** \param mode State mode value
   ** auto fetch Cursor coordinates
   */
  explicit State(e_mode &mode);

  /** Constructor
   ** \param mode State mode value
   ** auto fetch Cursor coordinates
   */
  State(e_mode mode, std::shared_ptr<Menu> menu);

  /** _mode getter
   ** \return _mode value
   */
  e_mode currentMode() { return _currentMode; }

  /** _menu getter
   ** \return _menu a pointer over current menu
   */
  std::shared_ptr<Menu> menu() { return _menu; }

  /** _cursorCoords getters
   ** \return _cursorCoords value
   */
  Coords cursorCoords() { return _cursorCoords; }

  /** \brief event manager getter
   ** \return _eventManager
   */
  std::shared_ptr<EventManager> eventManager() { return _eventManager; }


private:
  e_mode _currentMode; ///< State's mode
  std::shared_ptr<Menu> _menu; ///< menu state to save
  Coords _cursorCoords; ///< Cursor coordinates when the mode was activated
  std::shared_ptr<EventManager> _eventManager; ///< State related events
};

#endif /* !STATE_HH_ */
