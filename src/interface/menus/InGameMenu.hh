/**
 * \file
 * \date July 25, 2013
 * \author Zermingore
 */

#ifndef INGAMEMENU_HH_
# define INGAMEMENU_HH_


# include <interface/menus/Menu.hh>

enum class e_state;


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
   * \brief Builds the selection menu, filling the entries.
   * \param state The state about to be pushed.
   */
  void build(/* e_state state */);

  /// \brief executes action matching the selected entry.
  void executeEntry();
};

#endif /* !INGAMEMENU_HH_ */
