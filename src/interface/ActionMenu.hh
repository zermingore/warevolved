/*
 * ActionMenu.hh
 *
 *  Created on: Jul 24, 2013
 *      Author: Zermingore
 */

#ifndef ACTIONMENU_HH_
# define ACTIONMENU_HH_

# include <interface/EntriesMenu.hh>

/** \brief in-game ActionMenu class
 ** management of unit orders
 */
class ActionMenu : public EntriesMenu
{
public:
  ActionMenu();
  ~ActionMenu();

  /** \brief builds the Action menu, filling _entries
   */
  void build();

  /** \brief executes action matching _selectedEntry
   */
  void executeEntry();
};

#endif /* ACTIONMENU_HH_ */
