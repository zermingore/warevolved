/**
 * \file
 * \date June 2, 2019
 * \author Zermingore
 * \brief Car (specific Unit) class declaration
 */

#ifndef CAR_HH_
# define CAR_HH_

# include <string>
# include <game/units/Unit.hh>



/**
 * \class Car
 * \brief Specialization of Unit class
 */
class Car: public Unit
{
public:
  /**
   * \brief Default Constructor. Initializes characteristics motion, hp, ...
   */
  Car();
};

#endif /* !CAR_HH_ */
