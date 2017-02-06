/**
 * \file
 * \date October 24, 2016
 * \author Zermingore
 */

#ifndef STATE_MENU_HH_
# define STATE_MENU_HH_

# include <context/State.hh>

enum class e_state;

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
   * \brief Deleted default constuctor as we need to know in which state we are
   *   We cannot use Status::state() as the State is under construction
   */
  StateMenu() = delete;

  /**
   * \brief Constuctor: Builds the menu, registers to callbacks
   * \param state: State which is currently built
   */
  explicit StateMenu(e_state state);

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

//  void setAttribute();

  void getAttributeValue();


  void fetchAttributes();

  /**
   * \brief _menuCoords setter
   * \param c New menu coordinates
   */
  // void setMenuCoordinates(Coords c) { _menuCoords = c; }


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



  int test_void(std::shared_ptr<void> p);
  int test_int(std::shared_ptr<int> p);

  template<typename T>
  int test_t(T t);

};


#endif /* !STATE_MENU_HH_ */
