/**
 * \file
 * \date November 21, 2020
 * \author Zermingore
 * \namespace interface
 * \brief MenuBuildingUnit class declaration
 */

#ifndef MENU_BUILDING_UNIT_HH_
# define MENU_BUILDING_UNIT_HH_

# include <interface/menus/InGameMenu.hh>
# include <game/units/Unit.hh> // e_unit_role


namespace interface {


/**
 * \class MenuBuildingUnit
 * \brief Menu handling the actions available for a Unit
 */
class MenuBuildingUnit final: public InGameMenu
{
public:
  /**
   * \brief Default constructor
   */
  MenuBuildingUnit() = default;

  /**
   * \brief Add entries depending on the highlighted Unit
   */
  void build() override final;

  /**
   * \brief Draw the menu next to the Unit
   */
  void draw() override final;

  /// _unitIdx setter
  void setUnitIdx(int unitIdx) {
    _unitIdx = unitIdx;
  }


private:
  /**
   * \brief Get out of the Building
   * \note Pushes and activates the SELECT_EXIT_ZONE state
   */
  void getOut();

  int _unitIdx;         ///< Index in the crew member
};


} // namespace interface


#endif /* !MENU_BUILDING_UNIT_HH_ */