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
# include <game/items/Item.hh>
# include <resources/Image.hh>
# include <common/enums/ranks.hh>

/** \class This class describes a Soldier, not a unit
 ** a Soldier has a name, an inventory, ...
 */
class Soldier : public Unit
{
public:
  /** \brief Default Constructor
   ** creates a random Soldier (random name, characteristics, ...)
   */
  Soldier();

  /// \brief Destructor
  ~Soldier();

  /** \brief gets name and add grade abbreviated
   ** \return a string composed of the unit name and it's grade,
   **   separated by a space
   */
  std::string getName();


private:
  Item *_equipedWeapon; ///< can be a rifle, a shovel, ...
  std::vector<Item *> _gear; ///< Equipped items
  std::vector<Item *> _inventory; ///< non equipped items
  e_rank _rank; ///< military grade
  std::string _fullName; ///< soldier's full name (first and last names)

  short _driverLevel; ///< driver level
  short _mechanicsLevel; ///< mechanics level
  short _gunnerLevel; ///< mechanics level

  std::vector<Unit *> _teamMembers; ///< list of other team members
};

#endif /* !SOLDIER_HH_ */
