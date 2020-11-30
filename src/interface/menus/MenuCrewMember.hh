/**
 * \file
 * \date September 23, 2019
 * \author Zermingore
 * \namespace interface
 * \brief MenuCrewMember class declaration
 */


#ifndef MENU_CREW_MEMBER_HH_
# define MENU_CREW_MEMBER_HH_

# include <interface/menus/InGameMenu.hh>
# include <game/units/Unit.hh> // e_unit_role


namespace interface {


/**
 * \class MenuCrewMember
 * \brief Menu handling the actions available for a crew member
 */
class MenuCrewMember final: public InGameMenu
{
public:
  /**
   * \brief Default constructor
   */
  MenuCrewMember() = default;

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

  e_unit_role _role;    ///< Role concerned by this menu
  int _unitIdx;         ///< Index in the crew member
};


} // namespace interface


#endif /* !MENU_CREW_MEMBER_HH_ */
