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


  /// _active setter
  void setActive(bool active) {
    _active = active;
  }

  /// _hidden setter
  void setHidden(bool hide) {
    _hidden = hide;
  }

  /// _role setter
  void setRole(e_unit_role role) {
    _role = role;
  }



private:
  /**
   * \brief Get out of the Vehicle
   * \note Pushes and activates the SELECT_DROP_ZONE state
   */
  void getOut();


  bool _active = false; ///< True if the menu has the focus
  bool _hidden = false; ///< True to not draw the menu
  e_unit_role _role;    ///< Role concerned by this menu
  int _unitRoleIdx;
};


} // namespace interface


#endif /* !MENU_CREW_MEMBER_HH_ */
