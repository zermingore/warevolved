/**
 * \file
 * \date Feb 19, 2013
 * \author Zermingore
 * \brief Handy aliases on data structures
 */

#ifndef USING_HH_
# define USING_HH_

# include <cstddef> // size_t
# include <common/structures/Vector.hh>
# include <SFML/Graphics/Color.hpp>


/// Handy using for a color, only here dependent from a graphic library
using Color = sf::Color; // SFML dependent


/**
 * \class Coords
 * \brief Handy coordinates representation
 * \note Based on a Vector2, independent from math / graphic library
 */
class Coords: public Vector2<size_t>
{
public:
  /**
   * \brief Default constructor. Initial coordinates: (0, 0)
   * \note Initializes the c and l references on Vector2 x y
   */
  Coords()
    : Vector2<size_t> ()
    , c(x)
    , l(y)
  {
  }

  /**
   * \brief Constructor. Initializes a Coordinates with the given coordinates
   * \param a x, column coordinate
   * \param b y, line   coordinate
   * \note Initializes the c and l references on Vector2 x y
   */
  Coords(const size_t a, const size_t b)
    : Vector2<size_t> (a, b)
    , c(x)
    , l(y)
  {
  }


  /**
   * \brief Copy constructor
   */
  Coords(const Coords &coord)
    : Vector2<size_t> (coord.x, coord.y)
    , c(x)
    , l(y)
  {
  }

  /**
   * \brief Copy assignment operator
   */
  Coords& operator=(const Coords& r)
  {
    x = r.x;
    y = r.y;
    return *this;
  }



public: // explicitly specifying that these attributes are public
  size_t &c; ///< column coordinate
  size_t &l; ///< line   coordinate
};



#endif /* !USING_HH_ */
