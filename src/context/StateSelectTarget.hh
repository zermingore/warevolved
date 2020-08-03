/**
 * \file
 * \date February 22, 2017
 * \author Zermingore
 * \brief StateSelectTarget class declaration
 */

#ifndef SELECT_TARGET_HH_
# define SELECT_TARGET_HH_

# include <vector>
# include <memory>
# include <context/State.hh>
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
class StateSelectTarget: public State
{
public:
  /**
   * \brief registers to callbacks. Initializes the graphical attributes
   */
  StateSelectTarget();

  /**
   * \brief Default destructor; Clear cells highlights
   */
  ~StateSelectTarget() override;

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


  /// targets list from the PathFinding
  std::shared_ptr<std::vector<std::shared_ptr<Cell>>> _targets;

  size_t _index_target; ///< index of the selected target

  /// sprite associated to the highlight of the selected target
  std::shared_ptr<graphics::Sprite> _targetHighlight;

  Coords _attackLocation; ///< Cell from which the attack is performed

  std::shared_ptr<graphics::Sprite> _holoUnit; ///< 'holo' attacking unit sprite
  std::shared_ptr<PathFinding> _path; ///< Keep the pathfinding at hand
};


#endif /* !SELECT_TARGET_HH_ */
