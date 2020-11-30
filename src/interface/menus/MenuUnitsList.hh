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
   * \brief _confirmEntryActive setter
   * \param active true: display the confirm entry; false: hide it
   */
  void setConfirmEntryActive(bool active) {
    _confirmEntryActive = active;
  }

  /**
   * \brief Callbacks on selection array setter
   * \param callbacks Callbacks to call on Unit selection
   */
  void setEntryCallbacks(std::vector<std::function<void()>> callbacks) {
    _entryCbs = callbacks;
  }


private:
  bool _confirmEntryActive = true; ///< Should the 'Confirm' entry appear?
  std::vector<std::function<void()>> _entryCbs; ///< Callbacks on selection
  std::vector<std::shared_ptr<Unit>> _units; ///< Units list
};


} // namespace interface

# include <interface/menus/MenuUnitsList.hxx>

#endif /* !MENU_UNITS_LIST_HH_ */
