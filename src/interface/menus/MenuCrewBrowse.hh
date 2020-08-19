/**
 * \file
 * \date September 23, 2019
 * \author Zermingore
 * \namespace interface
 * \brief MenuCrewBrowse class declaration
 */

#ifndef MENU_CREW_BROWSE_HH_
# define MENU_CREW_BROWSE_HH_

# include <interface/menus/InGameMenu.hh>



namespace interface {


/**
 * \class MenuCrewBrowse
 * \brief Builds the menu displaying a vehicle's crew members list
 */
class MenuCrewBrowse final: public InGameMenu
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
   */
  void setActive(bool active) {
    _active = active;
  }



private:
  /**
   * \brief Closes the menu, confirming the crew management
   */
  void confirm();


  bool _active = true; ///< True if the menu has the focus

  std::shared_ptr<Unit> _selectedUnit; ///< Currently selected unit
  bool _confirmEntryActive = false; ///< Should the 'Confirm' entry appear?
};


} // namespace interface

#endif /* !MENU_CREW_BROWSE_HH_ */
