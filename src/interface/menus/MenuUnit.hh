/**
 * \file
 * \date December 1st, 2020
 * \author Zermingore
 * \namespace interface
 * \brief MenuUnit class declaration
 */

#ifndef MENU_UNIT
# define MENU_UNIT

# include <interface/menus/InGameMenu.hh>
# include <game/units/Unit.hh> // e_unit_role


namespace interface {


/**
 * \class MenuUnit
 * \brief Handle actions available for a Unit (in a given container)
 * \note Allowed templates: Building Vehicle
 */
template<typename T>
class MenuUnit final: public InGameMenu
{
public:
  /**
   * \brief Default constructor
   */
  MenuUnit() = default;

  /**
   * \brief Add entries depending on the highlighted crew member
   */
  void build() override final;

  /**
   * \brief Draw the menu next to the member
   */
  void draw() override final;


  /// _role setter
  void setUnitIdx(int unitIdx) {
    _unitIdx = unitIdx;
  }


private:
  /**
   * \brief Get out of the Vehicle
   * \note Pushes and activates the SELECT_DROP_ZONE state
   */
  void getOut();

  e_unit_role _role; ///< Role concerned by this menu
  int _unitIdx;      ///< Index in the crew member
};


} // namespace interface

# include <interface/menus/MenuUnit.hxx>

#endif /* !MENU_UNIT */
