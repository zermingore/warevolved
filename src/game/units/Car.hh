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
  bool canOpenFire() const override final;

  /**
   * \brief Add the given unit to the Car
   * \param unit Unit getting in the car (adding it to the crew)
   * \note As default: The driver will be added; then the copilot
   * \todo Handle passengers
   * \todo Check if the given Unit can get in (ex: a tank cannot get in a car)
   */
  bool addToCrew(std::shared_ptr<Unit> unit) override final;
};

#endif /* !CAR_HH_ */
