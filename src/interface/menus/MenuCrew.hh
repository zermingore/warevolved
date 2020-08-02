/**
 * \file
 * \date September 7, 2019
 * \author Zermingore
 * \brief interface::MenuCrew class declaration
 */


#ifndef MENU_CREW_HH_
# define MENU_CREW_HH_

# include <interface/menus/InGameMenu.hh>
# include <common/enums/states.hh>

enum class e_state;

class PathFinding;



namespace interface {


/**
 * \class MenuCrew
 * \brief Builds the menu displaying possible actions for a unit being played
 */
class MenuCrew final: public InGameMenu
{
public:
  /**
   * \brief Defaulted constructor
   */
  MenuCrew() = default;

  /**
   * \brief default destructor
   */
  ~MenuCrew() override = default;


  /**
   * \brief Builds an action menu according to its State
   */
  void build() override final;

  /**
   * \brief Draw the menu and the path finding
   */
  void draw() override final;



private:
  /**
   * \brief Closes the action menu
   *   rolls back to the previous action menu if any, or pops every State
   */
  void cancel() override final;


  Coords _clickedCell; ///< Clicked cell where this menu was invoked

  std::shared_ptr<Unit> _selectedUnit; ///< Vehicle containing the crew

  /// Get free cells around the Vehicle
  std::unique_ptr<PathFinding> _pathFinding;
};


} // namespace interface

#endif /* !MENU_ACTION_HH_ */
