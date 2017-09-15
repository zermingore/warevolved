/**
 * \file
 * \date February 22, 2017
 * \author Zermingore
 */

#ifndef SELECT_TARGET_HH_
# define SELECT_TARGET_HH_

# include <vector>
# include <memory>
# include <context/State.hh>
# include <graphics/graphic_types.hh>

class Cell;

namespace resources {
  class Image;
}


/**
 * \class StateSelectTarget
 * \brief State in charge of the target selection
 */
class StateSelectTarget: public State
{
public:
  /**
   * \brief registers to callbacks. Initializes the graphical attributes
   */
  StateSelectTarget();

  /**
   * \brief Default destructor
   */
  ~StateSelectTarget() = default;

  /**
   * \brief re-build the menu.
   */
  void resume() override final;

  /**
   * \brief Draws the menu associated to the State
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


  ///< targets list from the PathFinding
  std::shared_ptr<std::vector<std::shared_ptr<Cell>>> _targets;

  size_t _index_target; ///< index of the selected target


  ///< highlight of the selected target
  std::shared_ptr<resources::Image> _targetHighlightImage;

  ///< sprite associated to the highlight of the selected target
  std::shared_ptr<graphics::Sprite> _targetHighlight;

  Coords _attackLocation; ///< Cell from which the attack is performed

  std::shared_ptr<resources::Image> _holoUnit;       ///< 'holo' attacking unit
  std::shared_ptr<graphics::Sprite> _holoUnitSprite; ///< 'holo unit' sprite
};


#endif /* !SELECT_TARGET_HH_ */
