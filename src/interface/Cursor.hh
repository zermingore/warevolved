/**
 * \file
 * \date April 15, 2013
 * \author Zermingore
 */

#ifndef CURSOR_HH_
# define CURSOR_HH_

# include <common/include.hh>
# include <common/using.hh>
# include <interface/InterfaceElement.hh>


namespace interface {


/**
 * \class Cursor
 * \brief in-game Cursor class.
 *
 * Manages cursor shape, animation, motion.
 */
class Cursor: public InterfaceElement
{
public:
  /// Default Constructor
  Cursor();

  /**
   * \brief X (column) coordinate getter
   */
  size_t x() { return _coords.x; }

  /**
   * \brief Y (line) coordinate getter
   */
  size_t y() { return _coords.y; }

  /**
   * \brief _coords getter
   * \return _coords value
   */
  Coords coords() { return _coords; }

  /**
   * \brief coordinates setter.
   * \return Cursor's coordinates.
   */
  void setCoords(Coords coords) { _coords = coords; }

  /**
   * \brief Sets the map limits according to the given parameters.
   * \param nb_columns number of columns in the map
   * \param nb_lines number of lines in the map
   */
  void setLimits(size_t nb_columns, size_t nb_lines);


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


  /**
   * \brief Updates the graphics properties of the cursor
   */
  void update();



private:
  // map attributes
  size_t _nbColumns; ///< number of columns in map
  size_t _nbLines;   ///< number of Lines in map
  Coords _coords;    ///< Cursor Coordinates (in cells)
  sf::Color _color;  ///< cursor's color
};


} // namespace interface


#endif /* !CURSOR_HH_ */
