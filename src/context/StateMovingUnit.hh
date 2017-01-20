/**
 * \file
 * \date November 25, 2016
 * \author Zermingore
 */
#ifndef STATE_MOVING_UNIT_HH_
# define STATE_MOVING_UNIT_HH_

# include <context/State.hh>
# include <common/using.hh> // Coords


/**
 * \class StateMovingUnit
 * \brief State active while moving a unit on the map
 */
class StateMovingUnit: public State
{
public:
  /**
   * \brief registers to callbacks
   * \param cursor_coords cursor coordinates
   */
  StateMovingUnit();

  /**
   * \brief exits the current State
   */
  void exit();


private:
  // Units motion
  void moveUnitUp();
  void moveUnitDown();
  void moveUnitLeft();
  void moveUnitRight();

  Coords _originalCoords;   ///< original unit coordinates
  Coords _holoUnitPosition; ///< Unit position 'cursor'
};


#endif /* !STATE_MOVING_UNIT_HH_ */
