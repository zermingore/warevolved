/**
 * \file
 * \date Feb 19, 2013
 * \author Zermingore
 * \brief Coord class declaration; Handy aliases on data structures
 */

#ifndef COMMON_USING_HH_
# define COMMON_USING_HH_

# include <utility>
# include <optional>
# include <cstddef> // size_t
# include <structures/Vector.hh>


/// Used in Inventory context (Weapon / Unit effective range)
using Range = std::pair<std::optional<size_t>, std::optional<size_t>>;


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
  Coords() noexcept
    : Vector2<size_t> (0, 0)
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
  Coords(const size_t a, const size_t b) noexcept
    : Vector2<size_t> (a, b)
    , c(x)
    , l(y)
  {
  }


  /**
   * \brief Copy constructor
   * \param coord Coordinates to copy from
   */
  Coords(const Coords &coord) noexcept
    : Vector2<size_t> (coord.x, coord.y)
    , c(x)
    , l(y)
  {
  }

  /**
   * \brief Copy assignment operator
   * \param r Right member of the assignement
   */
  Coords& operator=(const Coords& r)
  {
    x = r.x;
    y = r.y;
    c = r.x;
    l = r.y;
    return *this;
  }

  /**
   * \brief Equality operator
   * \param r Right member to test the equality with
   * \note x, c must be equal and y, l too
   */
  bool operator==(const Coords& r) const
  {
    return ((x == r.x && y == r.y) && (c == r.c && l == r.l));
  }


public: // explicitly specifying that these attributes are public
  size_t &c; ///< column coordinate
  size_t &l; ///< line   coordinate
};



#endif /* !COMMON_USING_HH_ */
