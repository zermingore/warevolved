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


  // ___________________________________________________________________________
  //                     Arithmetic Operators

  /**
   * \brief Addition assignment operator
   * \param rhs Right member
   * \return A reference on this
   */
  Vector2<T>& operator+=(const Vector2<T>& rhs)
  {
    x += rhs.x;
    y += rhs.y;
    return *this;
  }

  /**
   * \brief Addition operator
   * \param lhs Left member
   * \param rhs Right member
   * \return The result of (lhs.x + rhs.x; lhs.y + rhs.y)
   * \note Implemented using the assignment operator
   */
  friend Vector2<T> operator+(Vector2<T> lhs, const Vector2<T>& rhs)
  {
    lhs += rhs;
    return lhs;
  }


  /**
   * \brief Subtraction assignment operator
   * \param rhs Right member
   * \return A reference on this
   */
  Vector2<T>& operator-=(const Vector2<T>& rhs)
  {
    x -= rhs.x;
    y -= rhs.y;
    return *this;
  }

  /**
   * \brief Addition operator
   * \param lhs Left member
   * \param rhs Right member
   * \return The result of (lhs.x - rhs.x; lhs.y - rhs.y)
   * \note Implemented using the assignment operator
   */
  friend Vector2<T> operator-(Vector2<T> lhs, const Vector2<T>& rhs)
  {
    lhs -= rhs;
    return lhs;
  }

  /**
   * \brief Multiplication assignment operator
   * \param rhs Right member
   * \return A reference on this
   */
  Vector2<T>& operator*=(const Vector2<T>& rhs)
  {
    x *= rhs.x;
    y *= rhs.y;
    return *this;
  }

  /**
   * \brief Multiplication operator
   * \param lhs Left member
   * \param rhs Right member
   * \return The result of (lhs.x * rhs.x; lhs.y * rhs.y)
   * \note Implemented using the assignment operator
   */
  friend Vector2<T> operator*(Vector2<T> lhs, const Vector2<T>& rhs)
  {
    lhs *= rhs;
    return lhs;
  }


  /**
   * \brief Division assignment operator
   * \param rhs Right member
   * \return A reference on this
   * \note Crashes with integers; Returns infinity with floats on division by 0
   */
  Vector2<T>& operator/=(const Vector2<T>& rhs)
  {
    x /= rhs.x;
    y /= rhs.y;
    return *this;
  }

  /**
   * \brief Division operator.
   * \param lhs Left member
   * \param rhs Right member
   * \return The result of (lhs.x / rhs.x; lhs.y / rhs.y)
   * \note Implemented using the assignment operator
   */
  friend Vector2<T> operator/(Vector2<T> lhs, const Vector2<T>& rhs)
  {
    lhs /= rhs;
    return lhs;
  }

  // ___________________________________________________________________________



  /**
   * \brief stream operator: display x and y coordinates.
   */
  friend std::ostream& operator<<(std::ostream& os, const Vector2& v)
  {
    os << v.x << ", " << v.y;
    return os;
  }


  /**
   * \brief cast to SFML vector operator
   */
  operator sf::Vector2<T>()
  {
    return sf::Vector2f(x, y);
  }



public: // explicitly specifying that these attributes are public
  T x; ///< X component of the vector
  T y; ///< Y component of the vector
};



#endif /* !VECTOR_HH_ */
