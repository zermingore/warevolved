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
# include <context/StateSelectCell.hh>
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
class StateSelectDropZone: public StateSelectCell
{
public:
  /**
   * \brief Initializes _role to NONE
   */
  StateSelectDropZone();

  /**
   * \brief Default destructor
   */
  ~StateSelectDropZone() override = default;

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
   * \brief Validates the current drop zone selected
   */
  void validate() override;


  Coords _vehicleLocation; ///< Cell from which the drop is performed

  std::shared_ptr<graphics::Sprite> _holoUnit; ///< 'holo' dropping unit sprite

  e_unit_role _role; ///< Concerned Unit's role
  size_t _unitIdx; ///< Index in the crew[role] list
};


#endif /* !STATE_SELECT_DROP_ZONE_HH_ */
