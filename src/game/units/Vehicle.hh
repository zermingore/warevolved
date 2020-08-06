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


enum class e_unit_role;


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
  virtual ~Vehicle() override = default;

  /**
   * \brief Check if a crew member can operate the vehicle weapon
   *   or if it can self open fire
   * \note virtual pure
   * \return true if at least one crew member can open fire
   */
  virtual bool canOpenFire() const = 0;

  /**
   * \brief Returns crew list
   * \todo rename to 'crew()'
   */
  const auto& crew() const { return _crew; }

  /**
   * \brief Drop the given unit off the Vehicle at the given position
   * \param role Crew member occupying this role will be dropped off
   * \param location Cell where to drop the unit off
   */
  void dropOff(e_unit_role role, const Coords& location);

  /**
   * \brief _crew size getter
   * \return number of crew members
   */
  size_t crewSize() const override final { return _crew.size(); }

  // size_t roleProtection(); ///< Ex: In a pick-up: Gunner vs passenger

  /**
   * \brief Restore the dropped crew members
   * \note Called after cancelling the crew management
   */
  void restoreCrew();

  /**
   * \brief Clear the dropped crew members history
   * \note Called after confirming the crew management
   */
  void clearDroppedHistory() {
    _dropped.clear();
  }

  /**
   * \brief Check if the given unit can be a crew member
   * \return true if the Unit can get in and the crew is not full
   */
  bool canReceive(const std::shared_ptr<const Unit> unit) const override;



protected:
  std::map<e_unit_role, std::shared_ptr<Unit>> _crew; ///< Crew list (const key)

  /// Units dropped since the last cancel / beginning of the turn
  /// Used in order to cancel the drop
  std::map<e_unit_role, std::shared_ptr<Unit>> _dropped;

  size_t _maxCrewMembers = 0; ///< Number of seats (constant)
};



#endif /* !VEHICLE_HH_ */
