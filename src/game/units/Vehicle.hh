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
  Vehicle() : Unit() { }

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
   */
  const auto& getCrew() { return _crew; }

  /**
   * \brief Add the given \Unit to the crew
   */
  // void addToCrew(std::shared_ptr<Unit> unit) override;

  /**
   * \brief Unload the given Unit, at the given position
   */
  // void unload();

  // size_t roleProtection(); ///< Ex: In a pick-up: Gunner vs passenger



protected:
  std::map<e_unit_role, std::shared_ptr<Unit>>_crew; ///< Crew list (const keys)
  size_t _maxCrewMembers; ///< const; number of seats
};

#endif /* !VEHICLE_HH_ */
