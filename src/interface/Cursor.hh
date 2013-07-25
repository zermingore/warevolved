#ifndef CURSOR_HH_
# define CURSOR_HH_

# include <common/include.hh>
# include <resources/Image.hh>


/** \ brief in-game Cursor class
 ** Manages cursor shape, animation
 */

class Cursor
{
public:
  /** Default Constructor
   */
  Cursor();

  /** \brief Constructor which sets cursor, in function of map size
   ** \param nbColumns number of columns in map (in cells)
   ** \param nbLines number of lines in map (in cells)
   */
  Cursor(unsigned int nbColumns, unsigned int nbLines);

  /** \brief Destructor
   */
  ~Cursor();

  /** \brief _sprite getter
   */
  sf::Sprite getSprite();
  sf::Sprite getSprite(int offset_x, int offset_y);

  /** \brief X (column) coordinate getter
   */
  unsigned int getX();
  /** \brief Y (line) coordinate getter
   */
  unsigned int getY();

  /** \brief _coords getter
   ** \return _coords value
   */
  Coords getCoords();

  /** \brief X (column) coordinate setter
   */
  void setX(unsigned int x);
  /** \brief Y (line) coordinate setter
   */
  void setY(unsigned int y);

  /** \brief coordinates setter
   */
  void setCoords(Coords coords);

  // Cursor Motion
  /** \brief Move the cursor up
   ** \return true if the cursor moved
   */
  bool moveUp();
  /** \brief Move the cursor down
   ** \return true if the cursor moved
   */
  bool moveDown();
  /** \brief Move the cursor left
   ** \return true if the cursor moved
   */
  bool moveLeft();
  /** \brief Move the cursor right
   ** \return true if the cursor moved
   */
  bool moveRight();

  /** \brief draws the cursor
   */
  void draw();


private:
  // map attributes
  unsigned int _nbColumns;
  unsigned int _nbLines;

  Coords _coords; ///< Cursor Coordinates

  Image* _image;
  sf::Sprite* _sprite;
  sf::Texture* _texture;

  // middle of the SPRITE coordinates, avoid computing its value each frame
  sf::Vector2f _middle; ///< middle of the Cursor sprite
};

#endif /* !CURSOR_HH_ */
