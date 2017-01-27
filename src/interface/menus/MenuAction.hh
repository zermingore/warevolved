/**
 * \file
 * \date January 26, 2017
 * \author Zermingore
 *
 * interface::MenuAction declaration
 */


#ifndef MENU_MENU_ACTION_HH_
# define MENU_MENU_ACTION_HH_

# include <interface/menus/InGameMenu.hh>
# include <common/enums/states.hh>

enum class e_state;


namespace interface {


  // merge with MenuSelectionUnit ?
  // The result in MenuAction

  // A unit is selected -> we just need to test if it was 'used' before
  // (do not re-allow to move it)

  // But the actions are the same if it moved or not
  // (shoot, heal, ...)



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
  MenuAction(e_state state, Coords clicked_cell);

  /**
   * \brief default destructor
   */
  ~MenuAction() = default;


  /**
   * \brief Builds an action menu according to its State
   */
  void build() final;


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


  e_state _state;      ///< State related to this menu
  Coords _clickedCell; ///< Clicked cell where this menu was invoked
};


} // namespace interface

#endif /* !MENU_MENU_ACTION_HH_ */
