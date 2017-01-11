/**
 * \file
 * \date October 24, 2016
 * \author Zermingore
 */

#ifndef STATE_MENU_HH_
# define STATE_MENU_HH_

# include <context/State.hh>


/**
 * \class StateMenu
 * \brief The State which applies to any menu (browse, select entries, ...)
 */
class StateMenu: public State
{
public:
  /// registers to callbacks
  StateMenu();

  /// Destructor
  ~StateMenu() = default;


private:
  // Cursor motion
  void moveLeft();
  void moveRight();
  void moveDown();
  void moveUp();

  void validate();

  /**
   * \brief Callback associated with the exit menu event
   */
  void exit();
};


#endif /* !STATE_MENU_HH_ */
