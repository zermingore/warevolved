#ifndef UNIT_HH_
# define UNIT_HH_

# include <common/include.hh>
# include <resources/Image.hh>
# include <game/units/Team.hh>

class Team;

/** \brief Unit abstract class
 ** defines a generic unit
 */
// TODO abstract factory ?
// TODO abstract class
// (each have its own sprite [for rotation], but shared texture)
class Unit
{
public:
  /** \brief Default Constructor
   */
  Unit();

  explicit Unit(std::string &name);

  // __________________________ Getters / Setters __________________________ //
  inline int hp() { return _hp; } /// _hp getter
  inline int attackValue() { return _attackValue; } /// _attackValue getter

  /** \brief _posX getter
   ** \return _posX, x unit position (in px)
   */
  inline unsigned int posX() { return _posX; }

  /** \brief _posY getter
   ** \return _posY, y unit position (in px)
   */
  inline unsigned int posY() { return _posY; }

  /** \brief _cellX getter
   ** \return _cellX, x unit coordinate on the map
   */
  inline unsigned int cellX() { return _cellX; }

  /** \brief _cellY getter
   ** \return _cellY, y unit coordinate on the map
   */
  inline unsigned int cellY() { return _cellY; }

  /** \brief gets unit's position
   ** \return unit's cell location
   */
  inline Coords location() { return _location; }

  /** \brief sets unit's position
   ** \param location: cell's coordinates to set unit's position
   */
  void setLocation(Coords location);

  /** \brief unit's name getter
   ** \return unit's name value
   */
  inline virtual std::string name() { return _name; }

  /** \brief receive damages
   ** \return left Health Points
   */
  inline virtual int receiveDamages(unsigned int damages) { return _hp - damages; }

  /** \brief _motionValue getter
   ** \return number of cells the unit can cross in one turn
   */
  inline unsigned int motionValue() { return _motionValue; }

  /** \brief _playerId getter
   */
  inline unsigned int playerId() { return _playerId; }

  /** \brief _played getter
   ** \return true if the unit has already been played
   **   false otherwise
   */
  inline bool played() { return _played; }

  /** \brief sets Unit's coordinates
   ** \param cell_x x coordinate (column)
   ** \param cell_y y coordinate (line)
   */
  void setCellCoordinates(unsigned int cell_x, unsigned int cell_y);

  /** \brief sets Unit's player belonging
   ** \param player_id player's identifier
   */
  inline void setPlayerId(unsigned int player_id) { _playerId = player_id; }

  /** \brief _textureId getter
   ** \return Unit Texture id
   **   matching the one in the Resources Manager std::map
   */
  inline unsigned int textureId() { return _textureId; }

  /** \brief _textureId setter
   */
  inline void setTextureId(unsigned int texture_id) { _textureId = texture_id; }

  /** \brief _played setter
   ** \param unit's played status
   */
  inline void setPlayed(bool played) { _played = played; }

  /** \brief draws the Unit at it's position
   */
  void draw();

  /** \brief packs the Unit with \param unit
   */
  inline void pack(Unit *unit);

  /** \brief runs attack / strikes backs (if any) cycles
   */
  virtual void attack(Unit *target);


protected:
  unsigned int _textureId; ///< Texture id in the Resources Manager std::map
  unsigned int _imageId; ///< Image id in the Resources Manager std::map
  std::string _name; ///< Unit's class name

  int _hp; ///< Health Points (-1: infinite)
  int _attackValue; ///< target taken hp per shot (-1: instant death)

  unsigned int _posX; ///< x position (in px) // NOTE: absolute ? / relative to _cell ?
  unsigned int _posY; ///< y position (in px)
  //Coords _position; ///< Unit's cell relative position

  unsigned int _cellX; ///< x coordinate (column) on the map
  unsigned int _cellY; ///< y coordinate (row) on the map
  Coords _location; ///< Unit's cell coordinates

  unsigned int _motionValue; ///< Number of cells a unit can cross in one turn

  bool _played; ///< notify if the unit has already played this turn
  unsigned int _playerId; ///< the unit belongs to the player matching this id
  std::shared_ptr<Team> _team; ///< team in which this Unit belong to
  bool _targetable; ///< true if this unit can be under fire
};

#endif /* !UNIT_HH_ */
