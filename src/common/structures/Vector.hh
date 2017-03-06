/**
 * \file
 * \date Jul 24, 2013
 * \author Zermingore
 */

#ifndef VECTOR_HH_
# define VECTOR_HH_

# include <ostream>  // to overload the ostream operator


/**
 * \class Vector2
 * \brief Two dimensions vector.
 *
 * Allow not being dependent of a library vector implementation.
 */
template <typename T>
class Vector2
{
public:
  /// Default constructor. Creates a Vector2(0, 0).
  Vector2()
    : x(0)
    , y(0)
  {
  }

  /**
   * \brief Construct the vector with given coordinates.
   * \param a x coordinate.
   * \param b y coordinate.
   */
  Vector2(const T& a, const T& b)
    : x(a)
    , y(b)
  {
  }


  /**
   * \brief equality operator: compare x and y coordinates.
   *
   * Warning: Should not be used when the class is templated with floats !
   */
  bool operator==(const Vector2& b) {
    return (x == b.x && y == b.y);
  }

  /**
   * \brief stream operator: display x and y coordinates.
   */
  friend std::ostream& operator<<(std::ostream& os, const Vector2& v)
  {
    os << v.x << ", " << v.y;
    return os;
  }


  T x; ///< X component of the vector
  T y; ///< Y component of the vector
};



#endif /* !VECTOR_HH_ */
