/*
 * interface/Cursor.hh
 *
 *  Created on: April 15, 2013
 *      Author: Zermingore
 */

#ifndef CURSOR_HH_
# define CURSOR_HH_

# include <common/include.hh>
# include <common/using.hh>


/**
 * \class Cursor
 * \brief in-game Cursor class
 *
 * Manages cursor shape, animation, motion
 */
class Cursor
{
public:
  /**
   * \brief Default Constructor
   */
  Cursor();

  /**
   * \brief Constructor
   *
   * Sets the map limits according to the given parameters.
   *
   * \param nb_columns number of columns in the map
   * \param nb_lines number of lines in the map
   */
  Cursor(size_t nb_columns, size_t nb_lines);

  /**
   * \brief X (column) coordinate getter
   */
  unsigned int x() { return _coords.x; }
  /**
   * \brief Y (line) coordinate getter
   */
  unsigned int y() { return _coords.y; }

  /**
   * \brief _coords getter
   * \return _coords value
   */
  Coords coords() { return _coords; }

  /**
   * \brief coordinates setter
   */
  void setCoords(Coords coords) { _coords = coords; }

  /**
   * \brief sets _nbColumns and _nbLines
   */
  void setLimits(size_t nbColumns, size_t nbLines);


  // ____________________________ Cursor Motion ____________________________ //
  /**
   * \brief Move the cursor up
   * \return true if the cursor moved
   */
  bool moveUp();

  /**
   * \brief Move the cursor down
   * \return true if the cursor moved
   */
  bool moveDown();

  /**
   * \brief Move the cursor left
   * \return true if the cursor moved
   */
  bool moveLeft();

  /**
   * \brief Move the cursor right
   * \return true if the cursor moved
   */
  bool moveRight();


private:
  // map attributes
  size_t _nbColumns; ///< number of columns in map
  size_t _nbLines;   ///< number of Lines in map

  Coords _coords; ///< Cursor Coordinates

  std::string _image; ///< cursor's Image
  sf::Color _color;   ///< cursor's color

  // center of the SPRITE coordinates, avoid computing its value each frame
  //  sf::Vector2f _center; ///< center of the Cursor sprite
};

#endif /* !CURSOR_HH_ */
