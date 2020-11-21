/**
 * \file
 * \date November 21, 2020
 * \author Zermingore
 * \namespace interface
 * \brief MenuBuilding class declaration
 */

#ifndef MENU_BUILDING_HH_
# define MENU_BUILDING_HH_

# include <interface/menus/InGameMenu.hh>

class Building;

namespace interface {


/**
 * \class MenuBuilding
 * \brief Builds the menu displaying Uints Building's crew members list
 */
class MenuBuilding final: public InGameMenu
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


private:
  bool _active = true; ///< True if the menu has the focus

  std::shared_ptr<Building> _building; ///< Currently selected Building
};


} // namespace interface

#endif /* !MENU_BUILDING_HH_ */
