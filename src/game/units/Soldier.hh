/*
 * game/units/Soldier.hh
 *
 *  Created on: August 8, 2013
 *      Author: Zermingore
 */

#ifndef SOLDIER_HH_
# define SOLDIER_HH_

# include <game/units/Unit.hh>
# include <game/items/Item.hh>
# include <resources/Image.hh>
# include <common/enums/ranks.hh>
# include <common/Text.hh>

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

  /** \brief _rank getter
   ** \return the Unit's rank (as a string)
   */
  inline std::string getRankName() { return Text::name(_rank); }

  /** \brief _name getter
   ** \return the Unit's name
   */
  inline std::string name() { return _name; }

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

  // short _driverLevel; ///< driver level
  // short _mechanicsLevel; ///< mechanics level
  // short _gunnerLevel; ///< mechanics level

  std::vector<std::shared_ptr<Unit>> _teamMembers; ///< list of other team members
};

#endif /* !SOLDIER_HH_ */
