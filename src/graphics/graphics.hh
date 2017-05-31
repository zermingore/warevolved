/**
 * \file
 * \date Jan 11, 2015
 * \namespace interface
 * \brief InterfaceElement implementation
 */

#ifndef GRAPHICS_GRAPHICS_HH_
# define GRAPHICS_GRAPHICS_HH_

# include <SFML/System/Vector2.hpp>
# include <SFML/Graphics/Color.hpp>


namespace graphics {

// SFML: Using float.
// Because, from the SFML sources (SFML/System/Vector2.hpp):
// Note: although texture coordinates are supposed to be an integer
// amount of pixels, their type is float because of some buggy graphics
// drivers that are not able to process integer coordinates correctly.

using Pos2 = sf::Vector2f;
using Size2 = sf::Vector2f;
using component = float;  // component of Pos

using Color = sf::Color;
}


#endif /* !GRAPHICS_GRAPHICS_HH_ */
