/**
 * \file
 * \date September 23, 2019
 * \author Zermingore
 * \brief interface::MenuCrewBrowse declaration
 */


#ifndef MENU_CREW_BROWSE_HH_
# define MENU_CREW_BROWSE_HH_

# include <interface/menus/InGameMenu.hh>



namespace interface {


/**
 * \class MenuCrewBrowse
 * \brief Builds the menu displaying a vehicle's crew members list
 */
class MenuCrewBrowse: public InGameMenu
{
public:
  /**
   * \brief Default constructor
   */
  MenuCrewBrowse();

  /**
   * \brief default destructor
   */
  ~MenuCrewBrowse() override = default;


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
   * \brief Closes the menu
   *   rolls back to the previous action menu if any, or pops every State
   */
  void cancel() override final;

  /**
   * \brief Closes the menu, confirming the crew management
   */
  void confirm();


  std::shared_ptr<Unit> _selectedUnit; ///< Currently selected unit
};


} // namespace interface

#endif /* !MENU_CREW_BROWSE_HH_ */
