/*
 * interface/Cursor.hh
 *
 *  Created on: April 15, 2013
 *      Author: Zermingore
 */

#ifndef CURSOR_HH_
# define CURSOR_HH_

# include <common/include.hh>


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
  // inline std::shared_ptr<sf::Sprite> sprite() { return _sprite; }

  // std::shared_ptr<sf::Sprite> sprite(int offset_x, int offset_y);

  /** \brief sets the cursor color
   ** \param color the color to set
   */
  // inline void setColor(Color color) { _sprite->setColor(color); }
  inline void setColor(Color color) { _color = color; }

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

  /** \brief coordinates setter
   */
  inline void setCoords(Coords coords) { _coords = coords; }

  /** \brief sets _nbColumns and _nbLines
   */
  void setLimits(size_t nbColumns, size_t nbLines);


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
  // inline void draw() { _image.draw(); }


private:
  // map attributes
  size_t _nbColumns; ///< number of columns in map
  size_t _nbLines; ///< number of Lines in map

  Coords _coords; ///< Cursor Coordinates
  std::string _image; ///< Cursor's Image
  sf::Color _color; ///< cursor' s color

  // center of the SPRITE coordinates, avoid computing its value each frame
//  sf::Vector2f _center; ///< center of the Cursor sprite
};

#endif /* !CURSOR_HH_ */
