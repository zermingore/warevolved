/**
 * \file
 * \date August 8, 2013
 * \author Zermingore
 * \brief Soldier (specific Unit) class declaration
 */

#ifndef SOLDIER_HH_
# define SOLDIER_HH_

# include <string>
# include <game/units/Unit.hh>



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
};

#endif /* !SOLDIER_HH_ */
