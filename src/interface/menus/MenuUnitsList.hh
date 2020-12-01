/**
 * \file
 * \date November 30, 2020
 * \author Zermingore
 * \namespace interface
 * \brief MenuUnitsList class declaration
 */

#ifndef MENU_UNITS_LIST_HH_
# define MENU_UNITS_LIST_HH_

# include <interface/menus/InGameMenu.hh>

class Unit;


namespace interface {


/**
 * \class MenuUnitsList
 * \brief Builds a menu displaying a Units list (Building / Vehicle crew)
 * \note Allowed templates: Building Vehicle
 */
template<typename T>
class MenuUnitsList final: public InGameMenu
{
public:
  /**
   * \brief Builds the menu, initializing the entries
   */
  void build() override final;

  /**
   * \brief Draw the menu
   */
  void draw() override final;

  /**
   * \brief Add Building specific entries
   */
  void buildEntriesBuilding();

  /**
   * \brief Add Vehicle specific entries
   */
  void buildEntriesVehicle();

  /**
   * \brief Confirm the choices; close the menu
   */
  void confirm();
};


} // namespace interface

# include <interface/menus/MenuUnitsList.hxx>

#endif /* !MENU_UNITS_LIST_HH_ */
