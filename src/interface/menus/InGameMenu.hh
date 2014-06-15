/*
 * interface/menus/InGameMenu.hh
 *
 *  Created on: July 25, 2013
 *      Author: Zermingore
 */

#ifndef INGAMEMENU_HH_
# define INGAMEMENU_HH_

# include <interface/menus/EntriesMenu.hh>
# include <game/units/Unit.hh>
# include <game/applications/Battle.hh>

/** \brief in game menu class
 ** refers to the menu called when
 **   you pick a unit
 **   click on a void cell
 */
class InGameMenu: public EntriesMenu
{
public:
  /** \brief Default Constructor
   */
  InGameMenu();

  /** \brief Destructor
   */
  ~InGameMenu();

  /** \brief _battle setter
   */
  void setBattle(Battle *battle);

  /** \brief builds the selection menu, filling _entries
   ** \param mode The mode we're about to push
   */
  void build(e_mode mode);

  /** \brief executes action matching _selectedEntry
   */
  void executeEntry();


private:
  Unit *_selectedUnit; ///< Current selected unit
  Coords _selectedUnitPosition; ///< Position of the current selected unit
  Battle *_battle; ///< Current battle
};

#endif /* !INGAMEMENU_HH_ */
