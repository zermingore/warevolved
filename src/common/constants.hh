#ifndef CONSTANTS_HH_
# define CONSTANTS_HH_

# include <SFML/Graphics/Color.hpp>

# ifdef __unix__
#   define FOLDER_DELIMITER '/'
# else
#   define FOLDER_DELIMITER '\\'
# endif

# ifdef __unix__
#   define COLOR_NORMAL  "\x1B[0m"
#   define COLOR_RED     "\x1B[31m"
#   define COLOR_GREEN   "\x1B[32m"
#   define COLOR_YELLOW  "\x1B[33m"
#   define COLOR_BLUE    "\x1B[34m"
#   define COLOR_MAGENTA "\x1B[35m"
#   define COLOR_CYAN    "\x1B[36m"
#   define COLOR_WHITE   "\x1B[37m"
# else
#   define COLOR_NORMAL  ""
#   define COLOR_RED     ""
#   define COLOR_GREEN   ""
#   define COLOR_YELLOW  ""
#   define COLOR_BLUE    ""
#   define COLOR_MAGENTA ""
#   define COLOR_CYAN    ""
#   define COLOR_WHITE   ""
# endif

# define COLOR_ERROR   COLOR_RED
# define COLOR_WARNING COLOR_YELLOW
# define COLOR_SUCCESS COLOR_GREEN
# define COLOR_VERBOSE COLOR_BLUE

# define ON true
# define OFF false

// float equality test
# define EPSILON 0.000001

// resources paths
# define DEFAULT_IMAGE_PATH "resources/defaults/image.png"
# define DEFAULT_FONT_PATH "resources/defaults/font.ttf"

const sf::Color GRID_COLOR(202, 124, 0);

#endif /* !CONSTANTS_HH_ */
