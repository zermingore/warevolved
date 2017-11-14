/**
 * \file
 * \date August 8, 2013
 * \author Zermingore
 */

#ifndef SOLDIER_HH_
# define SOLDIER_HH_

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
   * \brief Default Constructor. Initializes characteristics motion, hp, ...
   */
  Soldier();


private:
  std::string _fullName; ///< soldier's full name (first and last names)
};

#endif /* !SOLDIER_HH_ */
