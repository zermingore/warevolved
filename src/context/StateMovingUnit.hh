/**
 * \file
 * \date November 25, 2016
 * \author Zermingore
 */

#ifndef STATE_MOVING_UNIT_HH_
# define STATE_MOVING_UNIT_HH_

# include <context/State.hh>
# include <common/using.hh> // Coords


namespace sf {
  class Sprite;
}

namespace resources {
  class Image;
}



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
   * \brief Resets the unit's sprite
   * \note It is necessary if the move was canceled
   */
  ~StateMovingUnit();

  /**
   * \brief exits the current State
   */
  void exit();


  /**
   * \brief Draw the holo unit (shadow of the unit) at _holoUnitPosition
   */
  virtual void draw();


  /**
   * \brief Resumes the menu. Updates its copy of the map dimensions
   */
  void resume() final;


private:
  // Units motion
  void moveUnitUp();
  void moveUnitDown();
  void moveUnitLeft();
  void moveUnitRight();

  Coords _originalCoords;   ///< original unit coordinates
  Coords _holoUnitPosition; ///< Unit position 'cursor' (in cell)

  std::shared_ptr<resources::Image> _holoUnit; ///< 'cursor' moving unit
  std::shared_ptr<sf::Sprite> _holoUnitSprite; ///< 'cursor' sprite

  size_t _nbColumns; ///< map number of columns
  size_t _nbLines;   ///< map number of lines
};


#endif /* !STATE_MOVING_UNIT_HH_ */
