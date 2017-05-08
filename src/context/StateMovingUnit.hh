/**
 * \file
 * \date November 25, 2016
 * \author Zermingore
 */

#ifndef CONTEXT_STATE_MOVING_UNIT_HH_
# define CONTEXT_STATE_MOVING_UNIT_HH_

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
  virtual void draw() override final;


  /**
   * \brief Resumes the menu. Updates its copy of the map dimensions
   */
  void resume() override final;


private:
  /// Move the unit up
  void moveUnitUp();

  /// Move the unit down
  void moveUnitDown();

  /// Move the unit left
  void moveUnitLeft();

  /// Move the unit right
  void moveUnitRight();


  Coords _originalCoords;   ///< original unit coordinates
  Coords _holoUnitPosition; ///< Unit position 'cursor' (in cell)

  std::shared_ptr<resources::Image> _holoUnit; ///< 'cursor' moving unit
  std::shared_ptr<sf::Sprite> _holoUnitSprite; ///< 'cursor' sprite

  size_t _nbColumns; ///< map number of columns
  size_t _nbLines;   ///< map number of lines
};


#endif /* !CONTEXT_STATE_MOVING_UNIT_HH_ */
