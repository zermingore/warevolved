/**
 * \file
 * \date May 21, 2013
 * \author Zermingore
 * \brief macro definitions
 */

#ifndef MACROS_HH_
# define MACROS_HH_


/**
 * \brief SFML key detection
 * \param feature key name auto expand _1 and _2 to this name
 * \return true if one of the two possible binding
 *     of a function has been triggered false otherwise
 */
# define PRESSED(x) sf::Keyboard::isKeyPressed(_keys[ x ##_1]) || \
    sf::Keyboard::isKeyPressed(_keys[ x ##_2])


#endif /* !MACROS_HH_ */
