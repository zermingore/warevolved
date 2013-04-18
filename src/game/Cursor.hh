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
  void moveUp();
  void moveDown();
  void moveLeft();
  void moveRight();


private:
  // map attributes
  unsigned int _nbColumns;
  unsigned int _nbLines;

  // Cursor specific
  unsigned int _x;
  unsigned int _y;

  sf::Sprite* _sprite;
  sf::Texture _texture;
  std::string _filename;

  sf::Clock _timer;

  // store the middle of the sprite coordinates
  sf::Vector2f _middle; // do not compute its value each frame
};

#endif /* !CURSOR_HH_ */
