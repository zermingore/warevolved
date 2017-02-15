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


/**
 * \class Soldier
 * \brief Specialization of Unit class
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
