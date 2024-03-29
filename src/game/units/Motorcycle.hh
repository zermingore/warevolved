/**
 * \file
 * \date March 20, 2020
 * \author Zermingore
 * \brief Motorcycle (specific Unit) class declaration
 */

#ifndef MOTORCYCLE_HH_
# define MOTORCYCLE_HH_

# include <string>
# include <game/units/Vehicle.hh>



/**
 * \class Motorcycle
 * \brief Specialization of Unit class
 */
class Motorcycle: public Vehicle
{
public:
  /**
   * \brief Default Constructor. Initializes characteristics motion, hp, ...
   */
  Motorcycle();

  /**
   * \brief Can open fire depending on the presence of a passenger
   */
  bool canOpenFire() const override final;

  /**
   * \brief Add the given unit to the Motorcycle if its type allows it
   * \param unit Unit getting in the motorcycle (adding it to the crew)
   * \param role Role of the Unit getting in the motorcycle
   * \note Only a driver can be added
   */
  bool addToCrew(
    std::shared_ptr<Unit> unit,
    e_unit_role role = e_unit_role::DRIVER) override final;

  /**
   * Update the Sprite, depending on the crew
   */
  void updateSprite() override final;
};

#endif /* !MOTORCYCLE_HH_ */
