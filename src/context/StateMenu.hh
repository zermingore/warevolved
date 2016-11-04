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

  /// Aborts the execution
  std::vector<int> getAttrList();


private:
  // Cursor motion
  void selectLeft();
  void selectRight();
  void selectDown();
  void selectUp();
  void validate();

  /**
   * \brief Callback associated with the exit menu event
   */
  void exit();
};


#endif /* !STATE_MENU_HH_ */
