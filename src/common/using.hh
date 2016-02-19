/*
 * common/using.hh
 *
 *  Created on: February 19, 2013
 *      Author: Zermingore
 */

#ifndef USING_HH_
# define USING_HH_

# include <cstddef> // size_t
# include <common/structures/Vector.hh>
# include <SFML/Graphics/Color.hpp>


/// Handy using for a color, only here dependent from a graphic library
using Color = sf::Color; // SFML dependent

/// Handy using for a vector, independent from math / graphic library
using Coords = Vector2<size_t>;


#endif /* !USING_HH_ */
