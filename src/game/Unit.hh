#ifndef UNIT_HH_
# define UNIT_HH_

# include <game/Cell.hh>


/** \brief Unit abstract class
 ** defines a generic unit
 */

class Unit
{
public:
  /** \brief Default Constructor
   */
  Unit();

  /** \brief Builds a new unit at cell's position
   ** sets _cell
   */
  Unit(Cell* cell);

  /** \brief Destructor
   */
  ~Unit(); // TODO virtual


  /** \brief _x getter
   ** \return _x, x unit position (in px)
   */
  unsigned int getX();

  /** \brief _y getter
   ** \return _y, y unit position (in px)
   */
  unsigned int getY();

  /** \brief _textureId getter
   ** \return Unit Texture id
   **   matching the one in the Resources Manager std::map
   */
  unsigned int getTextureId();

  /** \brief _textureId setter
   */
  void setTextureId(unsigned int texture_id);


private:
  unsigned int _textureId; ///< Texture id in the Resources Manager std::map
  // _faction; // TODO with a e_faction
  // std::string _name; // TODO ()use a global vector with all names, ...

  int _hp; ///< Health Points (-1: infinite)
  unsigned int _x; ///< x position (in px) // NOTE: absolute ? / relative to _cell ?
  unsigned int _y; ///< y position (in px)

  Cell *_cell;
};

#endif /* !UNIT_HH_ */
