/**
 * \file
 * \date May 3, 2013
 * \author Zermingore
 * \brief Unit class declaration and enum e_unit definition
 */

#ifndef UNIT_HH_
# define UNIT_HH_

# include <memory>
# include <cstddef> // size_t
# include <common/using.hh> // Coords
# include <graphics/graphic_types.hh>


class Inventory;

namespace graphics {
  class Sprite;
}



/**
 * \enum e_unit_role
 * \brief Different units roles in a crew
 */
enum class e_unit_role
{
  NONE = 0,  // Role not specified

  PASSENGER, // Eventually multiple passengers
  DRIVER,    // Or pilot
  COPILOT,   // May be necessary (airplane)
  LOADER,    // Ex: tank
  GUNNER,    // List (airplane)
  MECHANIC
};



/**
 * \enum e_unit
 * \brief Different units types
 */
enum class e_unit
{
  SOLDIER = 0,
  CAR,
  MOTORCYCLE,

  NB_UNITS,   // Counter
  NONE        // Invalid
};



/**
 * \class Unit
 * \brief Unit abstract class
 */
class Unit
{
public:
  /**
   * \brief Initialize the attributes with default values
   * \note The constructor is used to delegate a part of the initialization
   */
  Unit();

  /**
   * \brief Virtual default destructor
   */
  virtual ~Unit() = default;

  /**
   * \brief x coordinate on the map getter
   * \return x (column) coordinate on the Map
   */
  auto c() const { return _coords.c; }

  /**
   * \brief y unit coordinate on the map getter
   * \return y (line) coordinate on the Map
   */
  auto l() const { return _coords.l; }

  /**
   * \brief Get unit's position
   * \return Unit's Cell coordinates
   */
  auto coords() const { return _coords; }

  /**
   * \brief Get unit's position
   * \return Unit's Cell coordinates
   */
  auto oldCoords() const { return _oldCoords; }

  /**
   * \brief sets unit's position
   * \param coords New unit Cell's coordinates
   */
  void setCoords(const Coords coords) { _coords = coords; }

  /**
   * \brief sets old unit's position
   * \note Can be used, for instance to save coordinates before being moved
   */
  void stashCoords() { _oldCoords = _coords; }

  /**
   * \brief x coordinate on the map getter
   * \return x (column) coordinate on the Map
   */
  auto type() const { return _type; }

  /**
   * \brief _playerId getter
   * \return Id of the Player owning this Unit
   */
  auto playerId() const { return _playerId; }

  /**
   * \brief _played getter
   * \return true if the unit has already been played, false otherwise
   */
  auto played() const { return _played; }

  /**
   * \brief _moved getter
   * \return true if the unit has already been moved, false otherwise
   */
  auto moved() const { return _moved; }

  /**
   * \brief _inventory getter
   * \return A shared pointer on the Inventory
   */
  auto inventory() const { return _inventory; }

  /**
   * \brief sets Unit's player belonging
   * \param player_id player's identifier
   */
  void setPlayerId(size_t player_id) { _playerId = player_id; }

  /**
   * \brief _played setter
   * \param played unit's played status
   */
  void setPlayed(bool played) { _played = played; }

  /**
   * \brief _played setter
   * \param moved unit's moved status
   */
  void setMoved(bool moved) { _moved = moved; }

  /**
   * \brief _hp setter
   * \note allows negative values
   */
  void setHp(int hp) { _hp = hp; }

  /**
   * \brief Sprite color setter
   * \param color New Sprite color (RGBA)
   */
  void setColor(const graphics::Color& color);

  /**
   * \brief _hp getter
   * \return health points
   */
  auto hp() const { return _hp; }

  /**
   * \brief _maxHp getter
   * \return Maximal health points
   */
  auto maxHp() const { return _maxHp; }

  /**
   * \brief Attack value getter
   * \return Attack value in hit points
   */
  size_t attackValue() const;

  /**
   * \brief _motionValue getter
   * \return The number of Cells a Unit can cross in one turn
   */
  auto motionValue() const { return _motionValue; }

  /**
   * \brief _minRange getter
   * \return Minimal attack range (in Cells)
   */
  virtual size_t minRange() const { return _minRange; }

  /**
   * \brief _maxRange getter
   * \return Maximal attack range getter (in Cells)
   */
  virtual size_t maxRange() const { return _maxRange; }

  /**
   * \brief _sprite getter
   * \return a pointer on the Unit's sprite
   */
  auto sprite() const { return _sprite; }

  /**
   * \brief _canHaveCrew getter
   * \return true if the Unit has a crew (eventually empty); false otherwise
   */
  auto canHaveCrew() const { return _canHaveCrew; }

  /**
   * \brief Must be overriden to check if the given unit can be a crew member
   * \return false
   */
  bool virtual canReceive(
    [[maybe_unused]] const std::shared_ptr<const Unit> unit) const
  {
     return false;
  }

  /**
   * \brief Add the given Unit to the crew at the given role
   * \param unit Unit to add to the crew
   * \param role Role to give to the unit
   * \return true if the Unit could be added (false on full crew, role occupied)
   * \note Aborts the execution if called with the base class definition
   * \warning This method needs to be overloaded to be used
   */
  [[ noreturn ]]
  virtual bool addToCrew(std::shared_ptr<Unit> unit,
                         e_unit_role role = e_unit_role::NONE);

  /**
   * \brief *Always* returns 0
   * \return 0
   * \note must be overriden in Units using a crew
   */
  size_t virtual crewSize() const { return 0; }



protected:
  e_unit _type;        ///< Introspection; used for instance to save the Map
  Coords _coords;      ///< Unit's cell coordinates
  bool _played;        ///< notify if the unit has already played this turn
  bool _moved;         ///< notify if the unit has moved this turn
  Coords _oldCoords;   ///< Coordinates before moving (valid if _moved is true)
  size_t _playerId;    ///< the unit belongs to the player matching this id

  bool _canHaveCrew;   ///< Whether the Unit can host a crew
  size_t _motionValue; ///< Unit's motion value (not considering the terrains)
  int _hp;             ///< Health Points
  int _maxHp;          ///< Max Health Points
  size_t _attackValue; ///< Amount of damages dealing to other units

  size_t _minRange;    ///< Minimal required range for a unit to attack
  size_t _maxRange;    ///< Maximal range to attack a unit

  std::shared_ptr<graphics::Sprite> _sprite; ///< Unit Sprite

  std::shared_ptr<Inventory> _inventory; ///< Collection of Items
};



const std::map<const e_unit, const std::string> UNIT_TYPE_STR =
{
    { e_unit::SOLDIER,    "Soldier" }
  , { e_unit::CAR,        "Car" }
  , { e_unit::MOTORCYCLE, "Motorcycle" }
};



const std::map<const e_unit_role, const std::string> UNIT_ROLE_STR =
{
    { e_unit_role::NONE,      "None" }
  , { e_unit_role::PASSENGER, "Passenger" }
  , { e_unit_role::DRIVER,    "Driver" }
  , { e_unit_role::COPILOT,   "Co-Pilot" }
  , { e_unit_role::LOADER,    "Loader" }
  , { e_unit_role::GUNNER,    "Gunner" }
  , { e_unit_role::MECHANIC,  "Mechanic" }
};



#endif /* !UNIT_HH_ */
