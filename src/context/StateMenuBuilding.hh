/**
 * \file
 * \date November 20, 2020
 * \author Zermingore
 * \brief StateMenuBuilding class declaration
 */

#ifndef STATE_SELECT_BUILDING_UNIT_HH_
# define STATE_SELECT_BUILDING_UNIT_HH_

# include <memory>
# include <context/State.hh>

enum class e_state;

namespace interface
{
  class MenuBuildingUnits;
  class MenuBuildingUnit;
}



/**
 * \class StateMenu
 * \brief The State which applies to any menu (browse, select entries, ...)
 */
class StateMenuBuilding: public State
{
public:
  /**
   * \brief Default constuctor
   */
  StateMenuBuilding();

  /**
   * \brief default destructor
   */
  ~StateMenuBuilding() override = default;


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
   * \brief Adjust the menu member hidden flag
   */
  void setFocusMenuMember();


  std::shared_ptr<interface::MenuBuildingUnits> _menuUnits; ///< Crew members
  std::shared_ptr<interface::MenuBuildingUnit> _menuUnit; ///< Member actions

  Coords _menuUnitsCoords; ///< List of Units Menu's coordinates
  Coords _menuUnitCoords;  ///< Unit Menu's coordinates

  bool _browseUnits; ///< Browse the Units or its actions
  int _unitIdx = 0;  ///< Currently selected crew Unit index
};

#endif /* !STATE_SELECT_BUILDING_UNIT_HH_ */
