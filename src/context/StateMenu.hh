/**
 * \file
 * \date October 24, 2016
 * \author Zermingore
 */

#ifndef STATE_MENU_HH_
# define STATE_MENU_HH_

# include <context/State.hh>

namespace interface {
  class InGameMenu;
}


/**
 * \class StateMenu
 * \brief The State which applies to any menu (browse, select entries, ...)
 */
class StateMenu: public State
{
public:
  /**
   * \brief Default constuctor: Builds the menu, registers to callbacks
   */
  StateMenu();

  /// Destructor
  ~StateMenu() = default;

  /**
   * \brief Save the menu coordinates.
   * \todo also save selected entry.
   */
  void suspend();

  /**
   * \brief re-build the menu.
   */
  void resume();

  /**
   * \brief Draws the menu associated to the State
   */
  void draw();


private:
  // Cursor motion in the menu
  void moveDown();
  void moveUp();

  /// Validate menu entry selection
  void validate();

  /**
   * \brief Callback associated with the exit menu event
   */
  void exit();


  std::shared_ptr<interface::InGameMenu> _menu; ///< menu associated to the state

  Coords _menuCoords; ///> menu coordinates
};


#endif /* !STATE_MENU_HH_ */
