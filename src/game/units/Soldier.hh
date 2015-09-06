/*
 * game/units/Soldier.hh
 *
 *  Created on: August 8, 2013
 *      Author: Zermingore
 */

#ifndef SOLDIER_HH_
# define SOLDIER_HH_

# include <vector>
# include <string>
# include <game/units/Unit.hh>
# include <common/enums/ranks.hh>

class Item;


/** \class This class describes a Soldier, not a unit
 ** a Soldier has a name, an inventory, ...
 */
class Soldier: public Unit
{
public:
  /** \brief Default Constructor
   ** creates a random Soldier (random name, characteristics, ...)
   */
  Soldier();

  /** \brief gets name and add grade abbreviated
   ** \return a string composed of the unit name and it's grade,
   **   separated by a space
   */
  std::string name();

  /** \brief fills the given Menu with the possible Entries,
   **   according to the Unit skills
   ** \param menu inGameMenu in which we add relevant entries
   ** virtual method
   */
  void fillActions(std::vector<MenuEntry>& menu);


private:
  std::shared_ptr<Item> _equipedWeapon; ///< can be a rifle, a shovel, ...
  std::vector<std::shared_ptr<Item>> _gear; ///< Equipped items
  std::vector<std::shared_ptr<Item>> _inventory; ///< non equipped items
  rank _rank; ///< military grade
  std::string _fullName; ///< soldier's full name (first and last names)

  // short _driverLevel; ///< driver level
  // short _mechanicsLevel; ///< mechanics level
  // short _gunnerLevel; ///< mechanics level

  std::vector<std::shared_ptr<Unit>> _teamMembers; ///< list of other team members
};

#endif /* !SOLDIER_HH_ */
