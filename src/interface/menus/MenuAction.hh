/**
 * \file
 * \date January 26, 2017
 * \author Zermingore
 * \namespace interface
 * \brief MenuAction class declaration
 */

#ifndef MENU_ACTION_HH_
# define MENU_ACTION_HH_

# include <interface/menus/InGameMenu.hh>

enum class e_state;

class PathFinding;



namespace interface {


/**
 * \class MenuAction
 * \brief Builds the menu displaying possible actions for a unit being played
 */
class MenuAction final: public InGameMenu
{
public:
  /**
   * \brief deleted default constructor
   */
  MenuAction() = delete;

  /**
   * \brief Constructor
   * \param state State in which this menu will be used
   */
  explicit MenuAction(const e_state state);

  /**
   * \brief default destructor
   */
  ~MenuAction() override = default;


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

  /**
   * \brief Build the menu when selecting a Unit
   * \note Handle only the direct actions (without moving)
   */
  void buildMenuSelectionUnit();

  /**
   * \brief Build the menu specific entries after moving a Unit
   */
  void buildMenuAfterMovingUnit();

  /**
   * \brief Check if the unit is allowed to move. It is the case if
   *   - the unit didn't play (end of its action)
   *   - the unit didn't already moved
   * \return true if it is allowed to move; false otherwise
   */
  bool allowMove();

  /**
   * \brief Does the move (if possible)
   */
  void moveUnit();

  /**
   * \brief Order the Unit to wait
   */
  void waitUnit();

  /**
   * \brief Order the Unit to attack another one
   */
  void attackUnit();


  /**
   * \brief Handle the Unit Crew allowing to
   *   - drop some unit
   *   - \todo change their role
   */
  void manageCrew();


  e_state _state; ///< State related to this menu

  std::shared_ptr<Unit> _selectedUnit; ///< Currently selected unit

  /// Get targets list of the selected unit
  std::unique_ptr<PathFinding> _pathFinding;
};


} // namespace interface

#endif /* !MENU_ACTION_HH_ */
