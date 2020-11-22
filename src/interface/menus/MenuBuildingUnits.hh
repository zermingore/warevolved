/**
 * \file
 * \date September 23, 2019
 * \author Zermingore
 * \namespace interface
 * \brief MenuBuildingUnits class declaration
 */

#ifndef MENU_BUILDING_UNITS_HH_
# define MENU_BUILDING_UNITS_HH_

# include <interface/menus/InGameMenu.hh>

class Building;


namespace interface {


/**
 * \class MenuBuildingUnits
 * \brief Builds the menu displaying Building's Units list
 */
class MenuBuildingUnits final: public InGameMenu
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
   * \brief _active (focus) setter
   * \param active new _active value
   */
  void setActive(bool active) {
    _active = active;
  }

  /**
   * \brief _active (focus) setter
   * \param active true: display the confirm entry; false: hide it
   */
  void setConfirmEntryActive(bool active) {
    _confirmEntryActive = active;
  }


private:
  bool _active = true; ///< True if the menu has the focus

  std::shared_ptr<Building> _building; ///< Currently selected Building
  bool _confirmEntryActive = true; ///< Should the 'Confirm' entry appear?
};


} // namespace interface


#endif /* !MENU_BUILDING_UNITS_HH_ */
