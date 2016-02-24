/**
 * \file
 * \date Jul 24, 2013
 * \author Zermingore
 */

#ifndef VECTOR_HH_
# define VECTOR_HH_


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
  Vector2() : x(0), y(0)
  {}

  /**
   * \brief Construct the vector with given coordinates
   * \param a x coordinate
   * \param b y coordinate
   */
  Vector2(const T& a, const T& b) : x(a), y(b)
  {}


  T x; ///< X component of the vector
  T y; ///< Y component of the vector
};



#endif /* !VECTOR_HH_ */
