/**
 * \file
 * \date July 25, 2013
 * \author Zermingore
 */

#ifndef INGAMEMENU_HH_
# define INGAMEMENU_HH_


# include <interface/menus/Menu.hh>

enum class e_mode;


/**
 * \class InGameMenu
 * \brief Refers to the menu called when
 *   A unit is picked
 *   A void cell is clicked
 */
class InGameMenu: public Menu
{
public:
  /**
   * \brief builds the selection menu, filling the entries.
   * \param mode The mode about to be pushed.
   */
  void build(e_mode mode);

  /// \brief executes action matching the selected entry.
  void executeEntry();
};

#endif /* !INGAMEMENU_HH_ */
