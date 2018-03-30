/**
 * \file
 * \date May 3, 2013
 * \author Zermingore
 */

#ifndef UNIT_HH_
# define UNIT_HH_

# include <memory>
# include <cstddef> // size_t
# include <common/using.hh> // Coords
# include <graphics/graphic_types.hh>


namespace graphics {
  class Sprite;
}


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
   * \brief sets unit's position
   * \param coords New unit Cell's coordinates
   */
  void setCoords(const Coords coords) { _coords = coords; }

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
   * \brief _attackValue getter
   * \return Attack value in hit points
   */
  auto attackValue() const { return _attackValue; }

  /**
   * \brief _motionValue getter
   * \return The number of Cells a Unit can cross in one turn
   */
  auto motionValue() const { return _motionValue; }

  /**
   * \brief _minRange getter
   * \return Minimal attack range (in Cells)
   */
  auto minRange() const { return _minRange; }

  /**
   * \brief _maxRange getter
   * \return Maximal attack range getter (in Cells)
   */
  auto maxRange() const { return _maxRange; }

  /**
   * \brief sprite getter
   * \return a pointer on the Unit's sprite
   */
  auto sprite() const { return _sprite; }


protected:
  Coords _coords;      ///< Unit's cell coordinates
  bool _played;        ///< notify if the unit has already played this turn
  size_t _playerId;    ///< the unit belongs to the player matching this id

  size_t _motionValue; ///< Unit's motion value (not considering the terrains)
  int _hp;             ///< Health Points
  size_t _attackValue; ///< Amount of damages dealing to other units

  size_t _minRange;    ///< Minimal required range for a unit to attack
  size_t _maxRange;    ///< Maximal range to attack a unit

  std::shared_ptr<graphics::Sprite> _sprite; ///< Unit Sprite
};


#endif /* !UNIT_HH_ */
