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

class Item;


/** \class This class describes a Soldier, not a unit
 * a Soldier has a name, an inventory, ...
 */
class Soldier: public Unit
{
public:
  /**
   * \brief Default Constructor
   *
   * Creates a Soldier (random name, characteristics, ...)
   */
  Soldier();


private:
  std::string _fullName; ///< soldier's full name (first and last names)
};

#endif /* !SOLDIER_HH_ */
