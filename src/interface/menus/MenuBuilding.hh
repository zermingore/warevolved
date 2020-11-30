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


private:
  /**
   * \brief Closes the action menu
   *   rolls back to the previous action menu if any, or pops every State
   */
  void cancel() override final;


  std::shared_ptr<Building> _building; ///< Currently selected Building
};


} // namespace interface

#endif /* !MENU_BUILDING_HH_ */
