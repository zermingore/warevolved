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
   * \brief Add the given unit to the Car if its role allows it
   * \param unit Unit getting in the car (adding it to the crew)
   * \param role role to give to the Unit getting in the car
   * \note If the role is left empty: The driver will be added; then the copilot
   */
  bool addToCrew(
    std::shared_ptr<Unit> unit,
    e_unit_role role = e_unit_role::NONE) override final;

  /**
   * Update the Sprite, depending on the crew
   * \todo Clean manual pixel offsets
   */
  void updateSprite();
};

#endif /* !CAR_HH_ */
