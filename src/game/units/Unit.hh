#ifndef UNIT_HH_
# define UNIT_HH_

# include <memory>
# include <string>

# include <interface/menus/MenuEntry.hh>

class Team;
class Cell;

 /// \todo add Cell

 /// \todo abstract factory ?
// (each Unit have its own sprite [for rotation], but shared texture)

/**
 * \class Unit
 * \brief Unit abstract class
 */
class Unit
{
public:
  ///< \brief Default Constructor
  Unit();

  /**
   * \brief Default destructor
   */
  ~Unit() = default;


  /**
   * \brief x coordinate on the map getter
   * \return x (column) coordinate on the map
   */
  size_t x() { return _coords.x; }

  /**
   * \brief x unit coordinate on the map getter
   * \return y (line) coordinate on the map
   */
  size_t y() { return _coords.y; }

  /**
   * \brief gets unit's position
   * \return unit's cell coordinates
   */
  Coords coords() { return _coords; }

  /**
   * \brief sets unit's position and _played to true (we moved the unit)
   * \param coords: cell's coordinates to set unit's position
   */
  void setCoords(const Coords coords) { _coords = coords; }

  /**
   * \brief _playerId getter
   */
  unsigned int playerId() { return _playerId; }

  /**
   * \brief _played getter
   * \return true if the unit has already been played
   *   false otherwise
   */
  bool played() { return _played; }

  /**
   * \brief sets Unit's coordinates
   * \param coords Unit's new coordinates
   */
  void setCellCoordinates(Coords coords) { _coords = coords; }

  /**
   * \brief sets Unit's player belonging
   * \param player_id player's identifier
   */
  void setPlayerId(unsigned int player_id) { _playerId = player_id; }

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
  int hp() { return _hp; }

  /**
   * \brief _attackValue getter
   * \return attack value in hit points
   */
  size_t attackValue() { return _attackValue; }

  /**
   * \brief _motionValue getter
   */
  auto motionValue() { return _motionValue; }

  /**
   * \brief minimal attack range getter
   */
  auto minRange() { return _minRange; }

  /**
   * \brief maximal attack range getter
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

  std::shared_ptr<resources::Image> _image; ///< Unit Image
};


#endif /* !UNIT_HH_ */
