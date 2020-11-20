/**
 * \file
 * \date February 22, 2017
 * \author Zermingore
 * \brief StateSelectTarget class declaration
 */

#ifndef STATE_SELECT_TARGET_HH_
# define STATE_SELECT_TARGET_HH_

# include <vector>
# include <memory>
# include <context/StateSelectCell.hh>
# include <graphics/graphic_types.hh>

class Cell;
class PathFinding;

namespace graphics {
  class Sprite;
}


/**
 * \class StateSelectTarget
 * \brief State in charge of the target selection
 * \note This State is active after the Attack has been given
 */
class StateSelectTarget: public StateSelectCell
{
public:
  /**
   * \brief Initializes the graphical attributes
   */
  StateSelectTarget();

  /**
   * \brief Default destructor
   */
  ~StateSelectTarget() override = default;

  /**
   * \brief re-build the menu.
   */
  void resume() override final;

  /**
   * \brief Draws the menu associated to the State
   */
  void draw() override final;

  /**
   * \brief Fetch the attribute from the list
   * \note Expects one attribute: menu coordinates.
   * \note Aborts if no attribute was found
   */
  void fetchAttributes() override final;


private:
  /**
   * \brief Validates the current unit selected
   */
  void validate() override;


  Coords _attackLocation; ///< Cell from which the attack is performed

  std::shared_ptr<graphics::Sprite> _holoUnit; ///< 'holo' attacking unit sprite
  std::shared_ptr<PathFinding> _path; ///< Keep the pathfinding at hand
};


#endif /* !STATE_SELECT_TARGET_HH_ */
