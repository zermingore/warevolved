#ifndef UNIT_HH_
# define UNIT_HH_

# include <memory>
# include <string>

# include <game/units/Team.hh>
# include <interface/menus/MenuEntry.hh>

class Team;
class Cell;

/** \brief Unit abstract class
 ** defines a generic unit
 */
// TODO add Cell

// TODO abstract factory ?
// (each Unit have its own sprite [for rotation], but shared texture)
class Unit
{
public:
  ///< \brief Default Constructor
  Unit();

  /** \brief build a Unit, given its name
   ** \brief name Unit's name
   */
  explicit Unit(std::string &name);

  // __________________________ Getters / Setters __________________________ //
  inline int hp() { return _hp; } ///< _hp getter
  inline int attackValue() { return _attackValue; } ///< _attackValue getter
  inline Coords attackCoords() { return _attackCoords; } ///< _attackCoords getter

  /** \brief x coordinate on the map getter
   ** \return x (column) coordinate on the map
   */
  inline size_t x() { return _coords.x; }

  /** \brief x unit coordinate on the map getter
   ** \return y (line) coordinate on the map
   */
  inline size_t y() { return _coords.y; }

  /** \brief gets unit's position
   ** \return unit's cell coordinates
   */
  inline Coords coords() { return _coords; }

  /** \brief sets unit's position and _played to true (we moved the unit)
   ** \param coords: cell's coordinates to set unit's position
   */
  void setCoords(Coords coords);

  /** \brief sets unit's attack coordinates
   ** \param coords: cell's coordinates to set unit's position
   */
  inline void setAttackCoords(Coords coords) {  _attackCoords = coords; }

  /** \brief unit's name getter
   ** \return unit's name value
   */
  inline virtual std::string name() { return _name; }

  /** \brief receive damages
   ** \return left Health Points
   */
  virtual int receiveDamages(unsigned int damages);

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
   ** \param coords Unit's new coordinates
   */
  inline void setCellCoordinates(Coords coords) { _coords = coords; }

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

  //
  // __________ Targets management __________
  //
  /** \brief _targets getter
   ** \return _targets list of reachable targets
   */
  inline std::shared_ptr<std::vector<std::shared_ptr<Cell>>> targets()
  { return _targets; }
  /** \brief _targetIndex setter
   ** \param i _targetIndex value
   */
  inline void setTargetIndex(int i) { _targetIndex = i; }

  /** \brief selects the previous target in targets list
   ** \return selected target
   */
  std::shared_ptr<Cell> previousTarget();

  /** \brief selects the next target in targets list
   ** \return selected target
   */
  std::shared_ptr<Cell> nextTarget();

  //
  // __________ Actions management __________
  //
  /** \brief fills the given Menu with the possible Entries,
   **   according to the Unit skills
   ** \param menu inGameMenu in which we add relevant entries
   */
  virtual void fillActions(std::vector<MenuEntry>&) {}

  /** \brief runs attack / strikes backs (if any) cycles
   ** the target is _targets[_targetIndex]
   ** \return true if the unit is still alive, false otherwise
   */
  virtual bool attack(); // could return an attack status (killed, injured)

  /** \brief packs the Unit with \param unit
   */
  inline void pack(std::shared_ptr<Unit> unit);


protected:
  unsigned int _textureId; ///< Texture id in the Resources Manager std::map
  unsigned int _imageId; ///< Image id in the Resources Manager std::map
  std::string _name; ///< Unit's class name

  int _hp; ///< Health Points (-1: infinite)
  int _attackValue; ///< target taken hp per shot (-1: instant death)
  std::pair<int, int> _range; ///< Attack range
  Coords _coords; ///< Unit's cell coordinates
  Coords _attackCoords; ///< Unit's coordinates from where it attacks
  unsigned int _motionValue; ///< Number of cells a unit can cross in one turn
  bool _played; ///< notify if the unit has already played this turn
  unsigned int _playerId; ///< the unit belongs to the player matching this id
  std::shared_ptr<Team> _team; ///< team in which this Unit belong to
  bool _targetable; ///< true if this unit can be under fire

  ///< list of Cells the current Unit can interact with
  std::shared_ptr<std::vector<std::shared_ptr<Cell>>> _targets;
  int _targetIndex; ///< targeted Cell's index in _targets
};

#endif /* !UNIT_HH_ */
