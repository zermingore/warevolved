/*
 * interface/Cursor.hh
 *
 *  Created on: April 15, 2013
 *      Author: Zermingore
 */

#ifndef CURSOR_HH_
# define CURSOR_HH_

# include <common/include.hh>
# include <resources/Image.hh>


/** \brief in-game Cursor class
 ** Manages cursor shape, animation, motion
 */
class Cursor
{
public:
  /** Default Constructor
   */
  Cursor();

  /** \brief _sprite getter
   */
  inline std::shared_ptr<sf::Sprite> sprite() { return _sprite; }
  std::shared_ptr<sf::Sprite> sprite(int offset_x, int offset_y);

  /** \brief sets the cursor color
   ** \param color the color to set
   */
  inline void setColor(Color color) { _sprite->setColor(color); }

  /** \brief X (column) coordinate getter
   */
  inline unsigned int x() { return _coords.x; }
  /** \brief Y (line) coordinate getter
   */
  inline unsigned int y() { return _coords.y; }

  /** \brief _coords getter
   ** \return _coords value
   */
  inline Coords coords() { return _coords; }

  /** \brief X (column) coordinate setter
   */
  inline void setX(unsigned int x) { _coords.x = x; }
  /** \brief Y (line) coordinate setter
   */
  inline void setY(unsigned int y) { _coords.y = y; }

  /** \brief coordinates setter
   */
  inline void setCoords(Coords coords) { _coords = coords; }

  /** \brief sets _nbColumns and _nbLines
   */
  void setLimits(unsigned int nbColumns, unsigned int nbLines);


  // ____________________________ Cursor Motion ____________________________ //
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
  inline void draw() { _image.draw(); }


private:
  // map attributes
  size_t _nbColumns; ///< number of columns in map
  size_t _nbLines; ///< number of Lines in map

  Coords _coords; ///< Cursor Coordinates
  graphics::Image _image; ///< Cursor's Image
  std::shared_ptr<sf::Sprite> _sprite; ///< pointer over _image->sprite()

  // center of the SPRITE coordinates, avoid computing its value each frame
  sf::Vector2f _center; ///< center of the Cursor sprite
};

#endif /* !CURSOR_HH_ */
