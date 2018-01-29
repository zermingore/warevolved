/**
 * \file
 * \date Jul 24, 2013
 * \author Zermingore
 * \brief library independent 2 dimensions Vector
 */

#ifndef VECTOR_HH_
# define VECTOR_HH_

# include <ostream>  // to overload the ostream operator
# include <SFML/System/Vector2.hpp>


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

  /// Copy constructor.
  Vector2(const Vector2<T>& v)
    : x(v.x)
    , y(v.y)
  {
  }

  /// Build from generic SFML vector.
  template<typename U>
  Vector2(const sf::Vector2<U>& v)
    : x(static_cast<T> (v.x))
    , y(static_cast<T> (v.y))
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
   * \warning Should not be used when the class is templated with floats !
   */
  bool operator==(const Vector2& b) {
    return (x == b.x && y == b.y);
  }

  /**
   * \brief equality operator: compare x and y coordinates.
   * \warning Should not be used when the class is templated with floats !
   */
  Vector2& operator/(const sf::Vector2f& sfml_vector) {
    x = x / sfml_vector.x;
    y = y / sfml_vector.y;
    return *this;
  }

  /**
   * \brief stream operator: display x and y coordinates.
   */
  friend std::ostream& operator<<(std::ostream& os, const Vector2& v)
  {
    os << v.x << ", " << v.y;
    return os;
  }


  operator sf::Vector2<T>()
  {
    return sf::Vector2f(x, y);
  }


public: // explicitly specifying that these attributes are public
  T x; ///< X component of the vector
  T y; ///< Y component of the vector
};



#endif /* !VECTOR_HH_ */
