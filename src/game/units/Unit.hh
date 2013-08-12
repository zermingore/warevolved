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

  explicit Unit(std::string name);

  /** \brief Builds a new unit at cell's position
   ** sets _cell
   */
  //Unit(Cell* cell);

  /** \brief Destructor
   */
  virtual ~Unit();


  /** \brief _posX getter
   ** \return _posX, x unit position (in px)
   */
  unsigned int getPosX();

  /** \brief _posY getter
   ** \return _posY, y unit position (in px)
   */
  unsigned int getPosY();

  /** \brief _cellX getter
   ** \return _cellX, x unit coordinate on the map
   */
  unsigned int getCellX();

  /** \brief _cellY getter
   ** \return _cellY, y unit coordinate on the map
   */
  unsigned int getCellY();

  /** \brief gets unit's position
   ** \return unit's cell location
   */
  Coords getLocation();

  /** \brief sets unit's position
   ** \param location: cell's coordinates to set unit's position
   */
  void setLocation(Coords location);

  /** \brief unit's name getter
   ** \return unit's name value
   */
  virtual std::string getName();

  /** \brief _motionValue getter
   ** \return number of cells the unit can cross in one turn
   */
  unsigned int getMotionValue();

  /** \brief _playerId getter
   */
  unsigned int getPlayerId();

  /** \brief _played getter
   ** \return true if the unit has already been played
   **   false otherwise
   */
  bool getPlayed();

  /** \brief sets Unit's coordinates
   ** \param cell_x x coordinate (column)
   ** \param cell_y y coordinate (line)
   */
  void setCellCoordinates(unsigned int cell_x, unsigned int cell_y);

  /** \brief sets Unit's player belonging
   ** \param player_id player's identifier
   */
  void setPlayerId(unsigned int player_id);

  /** \brief _textureId getter
   ** \return Unit Texture id
   **   matching the one in the Resources Manager std::map
   */
  unsigned int getTextureId();

  /** \brief _textureId setter
   */
  void setTextureId(unsigned int texture_id);

  /** \brief _played setter
   ** \param unit's played status
   */
  void setPlayed(bool played);

  /** \brief draws the Unit at it's position
   */
  void draw();

  /** \brief packs the Unit with \param unit
   */
  void pack(Unit *unit);


protected:
  unsigned int _textureId; ///< Texture id in the Resources Manager std::map
  unsigned int _imageId; ///< Image id in the Resources Manager std::map
  std::string _name; ///< Unit's class name
  Image *_image; ///< Unit's image

  int _hp; ///< Health Points (-1: infinite)
  unsigned int _posX; ///< x position (in px) // NOTE: absolute ? / relative to _cell ?
  unsigned int _posY; ///< y position (in px)
  //Coords _position; ///< Unit's cell relative position

  unsigned int _cellX; ///< x coordinate (column) on the map
  unsigned int _cellY; ///< y coordinate (row) on the map
  Coords _location; ///< Unit's cell coordinates

  unsigned int _motionValue; ///< Number of cells a unit can cross in one turn

  bool _played; ///< notify if the unit has already played this turn
  unsigned int _playerId; ///< the unit belongs to the player matching this id
  Team *_team; ///< team in which this Unit belong to
};

#endif /* !UNIT_HH_ */
