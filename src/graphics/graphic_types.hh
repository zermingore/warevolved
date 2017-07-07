/**
 * \file
 * \date Jan 11, 2015
 * \namespace interface
 * \brief InterfaceElement implementation
 */

#ifndef GRAPHICS_GRAPHIC_TYPES_HH_
# define GRAPHICS_GRAPHIC_TYPES_HH_

# include <SFML/System/Vector2.hpp>
# include <SFML/Graphics/Color.hpp>
# include <SFML/Graphics.hpp>



namespace graphics {

// SFML: Using float for positions and sizes
// because, from the SFML sources (SFML/System/Vector2.hpp):
// Note: although texture coordinates are supposed to be an integer
// amount of pixels, their type is float because of some buggy graphics
// drivers that are not able to process integer coordinates correctly.

using RenderWindow = sf::RenderWindow;

using Pos2 = sf::Vector2f;
using Size2 = sf::Vector2f;
using Scale2 = sf::Vector2f;
using component = float;  // component of Pos, Size (Scale is logically float)

using Color = sf::Color;

using Sprite = sf::Sprite;
using Texture = sf::Texture;
using RectangleShape = sf::RectangleShape;
using Font = sf::Font;
}


#endif /* !GRAPHICS_GRAPHIC_TYPES_HH_ */