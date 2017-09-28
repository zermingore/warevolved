/**
 * \file
 * \date May 3, 2013
 * \author Zermingore
 */

#ifndef UNIT_HH_
# define UNIT_HH_

# include <memory>
# include <string>

# include <interface/menus/MenuEntry.hh>

class Team;


/// \todo abstract factory ?
// (each Unit have its own sprite [for rotation], but shared texture)

/**
 * \class Unit
 * \brief Unit abstract class
 */
class Unit
{
public:
  /**
   * \brief Initialize the attributes with default values
   */
  Unit();

  /**
   * \brief virtual default destructor
   */
  virtual ~Unit() = default;

  /**
   * \brief x coordinate on the map getter
   * \return x (column) coordinate on the Map
   */
  auto c() { return _coords.c; }

  /**
   * \brief x unit coordinate on the map getter
   * \return y (line) coordinate on the Map
   */
  auto l() { return _coords.l; }

  /**
   * \brief gets unit's position
   * \return unit's Cell coordinates
   */
  auto coords() { return _coords; }

  /**
   * \brief sets unit's position
   * \param coords New unit Cell's coordinates
   */
  void setCoords(const Coords coords) { _coords = coords; }

  /**
   * \brief _playerId getter
   * \return Id of the Player owning this Unit
   */
  auto playerId() { return _playerId; }

  /**
   * \brief _played getter
   * \return true if the unit has already been played, false otherwise
   */
  auto played() { return _played; }

  /**
   * \brief sets Unit's player belonging
   * \param player_id player's identifier
   */
  void setPlayerId(size_t player_id) { _playerId = player_id; }

  /**
   * \brief _played setter
   * \param unit's played status
   */
  void setPlayed(bool played) { _played = played; }

  /**
   * \brief _hp setter
   * \note allows negative values
   */
  void setHP(int hp) { _hp = hp; }

  /**
   * \brief _hp getter
   * \return health points
   */
  auto hp() { return _hp; }

  /**
   * \brief _attackValue getter
   * \return Attack value in hit points
   */
  auto attackValue() { return _attackValue; }

  /**
   * \brief _motionValue getter
   * \return The number of Cells a Unit can cross in one turn
   */
  auto motionValue() { return _motionValue; }

  /**
   * \brief _minRange getter
   * \return Minimal attack range (in Cells)
   */
  auto minRange() { return _minRange; }

  /**
   * \brief _maxRange getter
   * \return Maximal attack range getter (in Cells)
   */
  auto maxRange() { return _maxRange; }

  /**
   * \brief sprite getter
   * \return a pointer on the Unit's sprite
   */
  auto sprite() { return _image->sprite(); }

  /**
   * \brief image getter
   * \return a pointer on the Unit's image
   */
  auto image() { return _image; }


protected:
  Coords _coords;      ///< Unit's cell coordinates
  bool _played;        ///< notify if the unit has already played this turn
  size_t _playerId;    ///< the unit belongs to the player matching this id

  size_t _motionValue; ///< Unit's motion value (not considering the terrains)
  int _hp;             ///< Health Points
  size_t _attackValue; ///< Amount of damages dealing to other units

  size_t _minRange;    ///< Minimal required range for a unit to attack
  size_t _maxRange;    ///< Maximal range to attack a unit

  std::shared_ptr<resources::Sprite> _image; ///< Unit Image
};


#endif /* !UNIT_HH_ */
