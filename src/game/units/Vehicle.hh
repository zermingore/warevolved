/**
 * \file
 * \date August 11, 2019
 * \author Zermingore
 * \brief Vehicle (abstract Unit) class declaration
 */

#ifndef VEHICLE_HH_
# define VEHICLE_HH_

# include <string>
# include <game/units/Unit.hh>
# include <game/units/unit_roles.hh>



/**
 * \class Vehicle
 * \brief Specialization (still abstract) of Unit class
 */
class Vehicle: public Unit
{
public:
  /**
   * \brief Constructor: Calling base class constructor
   */
  Vehicle();

  /**
   * \brief Default desctructor
   */
  virtual ~Vehicle() = default;

  /**
   * \brief Check if a crew member can operate the vehicle weapon
   *   or if it can self open fire
   * \node virtual pure
   * \return true if at least one crew member can open fire
   */
  virtual bool canOpenFire() = 0;

  /**
   * \brief Returns crew list
   * \todo rename to 'crew()'
   */
  const auto& getCrew() { return _crew; }

  /**
   * \brief Drop the given unit off the Vehicle at the given position
   * \param role Crew member occupying this role will be dropped off
   * \param location Cell where to drop the unit off
   */
  void dropOff(e_unit_role role, Coords location);

  /**
   * \brief _crew size getter
   * \return number of crew members
   */
  size_t crewSize() const override final { return _crew.size(); }

  // size_t roleProtection(); ///< Ex: In a pick-up: Gunner vs passenger


protected:
  std::map<e_unit_role, std::shared_ptr<Unit>> _crew; ///< Crew list (const key)
  size_t _maxCrewMembers = 0; ///< Number of seats (constant)
};

#endif /* !VEHICLE_HH_ */
