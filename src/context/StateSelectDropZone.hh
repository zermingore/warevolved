/**
 * \file
 * \date September 24, 2019
 * \author Zermingore
 * \brief StateSelectDropZone class declaration
 */

#ifndef STATE_SELECT_DROP_ZONE_HH_
# define STATE_SELECT_DROP_ZONE_HH_

# include <vector>
# include <memory>
# include <context/State.hh>
# include <graphics/graphic_types.hh>

class Cell;

namespace graphics {
  class Sprite;
}

enum class e_unit_role;


/**
 * \class StateSelectDropZone
 * \brief State in charge of the drop zone selection
 * \note This State is active after the Drop Off or Get Out order
 */
class StateSelectDropZone: public State
{
public:
  /**
   * \brief registers to callbacks. Initializes the graphical attributes
   */
  StateSelectDropZone();

  /**
   * \brief Destructor; deactivates drop zones highlights
   */
  ~StateSelectDropZone() override;

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
   * \brief Select the previous free cell
   * \note loops on the last cell if called on the first one of the list
   */
  void selectPreviousZone();

  /**
   * \brief Highlights the next free cell in the list
   * \note loops on the first cell if called on the last one
   */
  void selectNextZone();

  /**
   * \brief Validates the current drop zone selected
   */
  void validate();

  /**
   * \brief Callback associated with the exit menu event
   */
  void exit();


  /// Free cells list from the PathFinding
  std::vector<std::shared_ptr<const Cell>> _zones;

  size_t _indexZone; ///< index of the selected zone

  /// sprite associated to the highlight of the selected zone
  std::shared_ptr<graphics::Sprite> _zoneHighlight;

  Coords _vehicleLocation; ///< Cell from which the drop is performed

  std::shared_ptr<graphics::Sprite> _holoUnit; ///< 'holo' dropping unit sprite

  e_unit_role _role; ///< Concerned Unit's role
  size_t _unitIdx; ///< Index in the crew[role] list
};


#endif /* !STATE_SELECT_DROP_ZONE_HH_ */
