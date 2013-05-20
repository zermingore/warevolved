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

  sf::Sprite getSprite();
  sf::Sprite getSprite(int offset_x, int offset_y);

  /** \brief X (column) coordinate getter
   */
  unsigned int getX();
  /** \brief Y (line) coordinate getter
   */
  unsigned int getY();

  /** \brief X (column) coordinate setter
   */
  void setX(unsigned int x);
  /** \brief Y (line) coordinate setter
   */
  void setY(unsigned int y);

  // Cursor Motion
  /** \brief Move the cursor up
   */
  void moveUp();
  /** \brief Move the cursor down
   */
  void moveDown();
  /** \brief Move the cursor left
   */
  void moveLeft();
  /** \brief Move the cursor right
   */
  void moveRight();

  void draw();


private:
  // map attributes
  unsigned int _nbColumns;
  unsigned int _nbLines;

  // Cursor specific
  unsigned int _x; ///< Cursor x (column) position
  unsigned int _y; ///< Cursor y (line) position

  Image* _image;

  sf::Sprite* _sprite;
  sf::Texture* _texture;

  // middle of the SPRITE coordinates, avoid computing its value each frame
  sf::Vector2f _middle; ///< middle of the Cursor sprite
};

#endif /* !CURSOR_HH_ */
