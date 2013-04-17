#ifndef CURSOR_HH_
# define CURSOR_HH_

# include <common/include.hh>


class Cursor
{
public:
  Cursor();
  ~Cursor();

  sf::Sprite getSprite();
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
  unsigned int _x;
  unsigned int _y;

  sf::Sprite* _sprite;
  sf::Texture _texture;
  std::string _filename;
};

#endif /* !CURSOR_HH_ */
