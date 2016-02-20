/*
 * interface/menus/InGameMenu.hh
 *
 *  Created on: July 25, 2013
 *      Author: Zermingore
 */

#ifndef INGAMEMENU_HH_
# define INGAMEMENU_HH_

# include <interface/menus/Menu.hh>
# include <common/enums/modes.hh>


/**
   * \brief in game menu class
 * refers to the menu called when
 *   you pick a unit
 *   click on a void cell
 */
class InGameMenu: public Menu
{
public:
  /**
   * \brief Default Constructor
   */
  InGameMenu() {}

  /**
   * \brief builds the selection menu, filling _entries
   * \param mode The mode we're about to push
   */
  void build(e_mode mode);

  /**
   * \brief executes action matching Menu::_selectedEntry
   */
  void executeEntry();
};

#endif /* !INGAMEMENU_HH_ */
