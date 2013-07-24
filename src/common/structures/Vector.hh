/*
 * Vector.hh
 *
 *  Created on: Jul 24, 2013
 *      Author: Zermingore
 *  Inspired from original SFML 2.0 Vector class
 */

#ifndef VECTOR_HH_
# define VECTOR_HH_


/** \brief Vector class
 ** it's here to avoid using SFML Vector,
 **   being dependent of a library
 */
template <class T> class Vector2
{
public:
    /** \brief Default constructor
     ** Creates a Vector2(0, 0).
     */
    Vector2() {
      x = 0;
      y = 0;
    }

    /** \brief Construct the vector with given coordinates
     ** \param x x coordinate
     ** \param x x coordinate
     */
    Vector2(T a, T b) {
      x = a;
      y = b;
    }

    T x; ///< X coordinate of the vector
    T y; ///< Y coordinate of the vector
};

typedef Vector2<unsigned int> Coords;


#endif /* !VECTOR_HH_ */
