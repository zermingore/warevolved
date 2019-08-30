/**
 * \file
 * \date June 2, 2019
 * \author Zermingore
 * \brief Car (specific Unit) class declaration
 */

#ifndef CAR_HH_
# define CAR_HH_

# include <string>
# include <game/units/Vehicle.hh>



/**
 * \class Car
 * \brief Specialization of Unit class
 */
class Car: public Vehicle
{
public:
  /**
   * \brief Default Constructor. Initializes characteristics motion, hp, ...
   */
  Car();

  /**
   * \brief Can open fire depending on the presence of a co-pilot
   */
  bool canOpenFire() override;

  /**
   * \brief Add the given unit to the Car
   * \note As default: The driver will be added; then the copilot and then passengers
   */
  bool addToCrew(std::shared_ptr<Unit> unit) override;
};

#endif /* !CAR_HH_ */
