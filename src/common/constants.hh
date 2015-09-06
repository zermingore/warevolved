#ifndef CONSTANTS_HH_
# define CONSTANTS_HH_

# include <SFML/Graphics/Color.hpp>

# ifdef __unix__
#   define FOLDER_DELIMITER '/'
# else
#   define FOLDER_DELIMITER '\\'
# endif

# define ON true
# define OFF false

// float equality test
# define EPSILON 0.000001

const sf::Color GRID_COLOR(202, 124, 0);

#endif /* !CONSTANTS_HH_ */
