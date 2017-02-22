/**
 * \file
 * \date February 22, 2017
 * \author Zermingore
 */

#ifndef STATE_SELECT_TARGET_HH_
# define STATE_SELECT_TARGET_HH_

# include <context/State.hh>


class StateSelectTarget: public State
{
public:
  /**
   * \brief registers to callbacks
   * \param cursor_coords cursor coordinates
   */
  StateSelectTarget();

  /**
   * \brief Resets the unit's sprite
   * \note It is necessary if the move was canceled
   */
  ~StateSelectTarget() = default;

  /**
   * \brief Save the menu coordinates.
   * \todo suspend() should also save selected entry.
   */
  void suspend() {}

  /**
   * \brief re-build the menu.
   */
  void resume() {}

  /**
   * \brief Draws the menu associated to the State
   */
  void draw();

  /**
   * \brief Fetch the attribute from thle list
   * \note Expects one attribute: menu coordinates.
   * \note Aborts if no attribute was found
   */
  void fetchAttributes() final {}


private:
  /**
   * \brief Select the previous unit
   * \note loops on the last unit if called on the first entry
   */
  void selectPreviousTarget();

  /**
   * \brief Highlights the entry on top of the current one
   * \note loops on the first unit if called on the last entry
   */
  void selectNextTarget();

  /**
   * \brief Validates the current unit selected
   */
  void validate();

  /**
   * \brief Callback associated with the exit menu event
   */
  void exit();
};


#endif /* !STATE_SELECT_TARGET_HH_ */
