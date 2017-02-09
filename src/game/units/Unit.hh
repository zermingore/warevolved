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
   * \brief build a Unit, given its name
   * \brief name Unit's name
   */
  explicit Unit(std::string &name);

  /**
   * \brief Default destructor
   */
  ~Unit() = default;


  // __________________________ Getters / Setters __________________________ //
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
  void setCoords(const Coords coords);

  /**
   * \brief unit's name getter
   * \return unit's name value
   */
  virtual std::string name() { return _name; }

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


protected:
  std::string _name; ///< Unit's class name

  Coords _coords; ///< Unit's cell coordinates
  bool _played; ///< notify if the unit has already played this turn
  unsigned int _playerId; ///< the unit belongs to the player matching this id
};

#endif /* !UNIT_HH_ */
