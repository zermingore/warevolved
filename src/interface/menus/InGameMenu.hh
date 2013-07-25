/*
 * InGameMenu.hh
 *
 *  Created on: Jul 25, 2013
 *      Author: Zermingore
 */

#ifndef INGAMEMENU_HH_
# define INGAMEMENU_HH_

# include <interface/menus/EntriesMenu.hh>

/** \brief in game menu class
 ** refers to the menu called when
 **   you pick a unit
 **   click on a void cell
 */
class InGameMenu: public EntriesMenu
{
public:
  InGameMenu();
  ~InGameMenu();

  /** \brief builds the selection menu, filling _entries
   */
  void build();

  /** \brief executes action matching _selectedEntry
   */
  void executeEntry();
};

#endif /* INGAMEMENU_HH_ */
