#ifndef CURSOR_HH_
# define CURSOR_HH_

# include <common/include.hh>


class Cursor
{
public:
  Cursor();
  Cursor(unsigned int nbColumns, unsigned int nbLines);
  ~Cursor();

  sf::Sprite getSprite();
  sf::Sprite getSprite(int offset_x, int offset_y);

  std::string getFilename();

  void setX(unsigned int x);
  void setY(unsigned int y);

  void setFilename(std::string);

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


private:
  // map attributes
  unsigned int _nbColumns;
  unsigned int _nbLines;

  // Cursor specific
  unsigned int _x; ///< Cursor x (column) position
  unsigned int _y; ///< Cursor y (line) position

  sf::Sprite* _sprite;
  sf::Texture _texture;
  std::string _filename;

  sf::Clock _timer;

  // middle of the SPRITE coordinates, avoid computing its value each frame
  sf::Vector2f _middle; ///< middle of the Cursor sprite
};

#endif /* !CURSOR_HH_ */
