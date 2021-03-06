/**
 * \file
 * \date October 24, 2016
 * \author Zermingore
 * \brief StateMenu class declaration
 */

#ifndef STATE_MENU_HH_
# define STATE_MENU_HH_

# include <memory>
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
   *   We cannot use game::Status::state() as the State is under construction
   */
  StateMenu() = delete;

  /**
   * \brief Constuctor: Builds the menu, registers to callbacks
   * \param state State which is currently built
   */
  explicit StateMenu(const e_state state);

  /**
   * \brief default destructor
   */
  ~StateMenu() override = default;


  /**
   * \brief Save the menu coordinates.
   * \todo suspend() should also save selected entry.
   */
  void suspend() override final;

  /**
   * \brief re-build the menu.
   */
  void resume() override final;

  /**
   * \brief Draws the menu associated to the State
   */
  void draw() override final;


  /**
   * \brief Fetch the attribute from thle list
   * \note Expects one attribute: menu coordinates.
   * \note Aborts if no attribute was found
   */
  void fetchAttributes() override final;



private:
  /**
   * \brief Highlights the entry bellow the current one
   * \note loops on the first entry if called on the last entry
   */
  void moveDown();

  /**
   * \brief Highlights the entry on top of the current one
   * \note loops on the last entry if called on the first one
   */
  void moveUp();

  /**
   * \brief Validates the current entry selected
   */
  void validate();

  /**
   * \brief Callback associated with the exit menu event
   */
  void exit();


  std::shared_ptr<interface::InGameMenu> _menu; ///< associated menu
  Coords _menuCoords;                           ///< menu coordinates
};


#endif /* !STATE_MENU_HH_ */
