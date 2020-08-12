/**
 * \file
 * \date September 22, 2019
 * \author Zermingore
 * \brief StateMenuCrew declaration
 */


#ifndef STATE_MENU_CREW_HH_
# define STATE_MENU_CREW_HH_

# include <memory>
# include <context/State.hh>

enum class e_state;

namespace interface
{
  class MenuCrewBrowse;
  class MenuCrewMember;
}



/**
 * \class StateMenu
 * \brief The State which applies to any menu (browse, select entries, ...)
 */
class StateMenuCrew: public State
{
public:
  /**
   * \brief Default constuctor
   */
  StateMenuCrew();

  /**
   * \brief default destructor
   */
  ~StateMenuCrew() override = default;


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
   * \brief Draws the menu crew
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
   * \brief Highlights the entry on top of the current one
   * \note loops on the last entry if called on the first one
   */
  void moveUp();

  /**
   * \brief Highlights the entry bellow the current one
   * \note loops on the first entry if called on the last entry
   */
  void moveDown();

  /**
   * \brief Highlights the entry on the left of the current one
   * \note Only applicable for crew member entry
   */
  void moveLeft();

  /**
   * \brief Highlights the entry on the right of the current one
   * \note Only applicable for crew member entry
   */
  void moveRight();

  /**
   * \brief Validates the current entry selected
   */
  void validate();

  /**
   * \brief Callback associated with the exit menu event
   */
  void exit();


  /**
   * \brief Restore the Vehicle status. This includes
   *   - The Vehicle coordinates
   *   - The dropped crew members
   */
  void cancel();

  /**
   * \brief Adjust the menu member hidden flag
   */
  void setFocusMenuMember();


  std::shared_ptr<interface::MenuCrewBrowse> _menuCrew;   ///< Crew members
  std::shared_ptr<interface::MenuCrewMember> _menuMember; ///< Member actions

  Coords _menuCrewCoords;   ///< Menu crew coordinates
  Coords _menuMemberCoords; ///< Menu member coordinates

  bool _browseMembers; ///< Browse the crew or a member's actions?
  int _unitIdx = 0;
};


#endif /* !STATE_MENU_CREW_HH_ */
