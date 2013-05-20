#ifndef UNIT_HH_
# define UNIT_HH_

# include <common/include.hh>
# include <resources/Image.hh>


/** \brief Unit abstract class
 ** defines a generic unit
 */

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
  ~Unit(); // TODO virtual


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

  /** \brief sets Unit's coordinates
   ** \param cell_x x coordinate (column)
   ** \param cell_y y coordinate (line)
   */
  void setCellCoordinates(unsigned int cell_x, unsigned int cell_y);

  /** \brief _textureId getter
   ** \return Unit Texture id
   **   matching the one in the Resources Manager std::map
   */
  unsigned int getTextureId();

  /** \brief _textureId setter
   */
  void setTextureId(unsigned int texture_id);

  /** \brief draws the Unit at it's position
   */
  void draw();

private:
  unsigned int _textureId; ///< Texture id in the Resources Manager std::map
  // _faction; // TODO with a e_faction

  unsigned int _imageId; ///< Image id in the Resources Manager std::map
  std::string _name; ///< unit's name

  Image *_image; ///< Unit's image

  int _hp; ///< Health Points (-1: infinite)
  unsigned int _posX; ///< x position (in px) // NOTE: absolute ? / relative to _cell ?
  unsigned int _posY; ///< y position (in px)

  unsigned int _cellX; ///< x coordinate (column) on the map
  unsigned int _cellY; ///< y coordinate (row) on the map


  //Cell *_cell;
};

#endif /* !UNIT_HH_ */
