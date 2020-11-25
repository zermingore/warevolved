/**
 * \file
 * \date November 19, 2020
 * \author Zermingore
 * \brief StateSelectExitZone class declaration
 */

#ifndef STATE_SELECT_EXIT_ZONE_HH_
# define STATE_SELECT_EXIT_ZONE_HH_

# include <mutex>
# include <vector>
# include <memory>
# include <context/StateSelectCell.hh>
# include <graphics/graphic_types.hh>

class Cell;
class Unit;
class Building;

namespace graphics {
  class Sprite;
}

enum class e_unit_role;


/**
 * \class StateSelectExitZone
 * \brief State in charge of the exit zone selection
 * \note This State is active trying to exit a Building
 */
class StateSelectExitZone: public StateSelectCell
{
public:
  /**
   * \brief Re-build the menu.
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
   * \brief Validates the current selected zone
   */
  void validate() override;


  std::shared_ptr<Building> _building; ///< Considered Building
  std::shared_ptr<graphics::Sprite> _holoUnit; ///< 'holo' dropping unit sprite
  Coords _buildingLocation; ///< Selected Cell belonging to the Building
  std::mutex _lock; ///< Avoid drawing while validating
  std::shared_ptr<Unit> _unit; ///< Unit exiting the Building
  size_t _unitIdx; ///< Unit index in the Building
};


#endif /* !STATE_SELECT_EXIT_ZONE_HH_ */
