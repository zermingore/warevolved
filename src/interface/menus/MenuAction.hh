/**
 * \file
 * \date January 26, 2017
 * \author Zermingore
 * \brief interface::MenuAction declaration
 */


#ifndef MENU_MENU_ACTION_HH_
# define MENU_MENU_ACTION_HH_

# include <interface/menus/InGameMenu.hh>
# include <common/enums/states.hh>

enum class e_state;


namespace interface {


/**
 * \class MenuAction
 * \brief Builds the menu displaying possible actions for a unit being played
 */
class MenuAction: public InGameMenu
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
  MenuAction(const e_state state, const Coords clicked_cell);

  /**
   * \brief default destructor
   */
  ~MenuAction() = default;


  /**
   * \brief Builds an action menu according to its State
   */
  void build() final;

  /**
   * \brief Draw the menu and the path finding
   */
  void draw() final;


private:
  /**
   * \brief Closes the action menu
   *   rolls back to the previous action menu if any, or pops every State
   */
  void cancel() final;

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


  e_state _state;      ///< State related to this menu
  Coords _clickedCell; ///< Clicked cell where this menu was invoked

  std::shared_ptr<Unit> _selectedUnit; ///< currently selected unit
};


} // namespace interface

#endif /* !MENU_MENU_ACTION_HH_ */
