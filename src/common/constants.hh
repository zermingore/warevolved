#ifndef CONSTANTS_HH_
# define CONSTANTS_HH_

# ifdef __unix__
#   define FOLDER_DELIMITER '/'
# else
#   define FOLDER_DELIMITER '\\'
# endif

// file paths
# define CURSORS_FOLDER "resources/cursors/"
# define TERRAINS_FOLDER "resources/terrains/"
# define UNITS_FOLDER "resources/units/"
# define INTERFACE_IN_GAME_MENU_FOLDER "resources/interface/in_game_menu/"

# define FONTS_FOLDER "resources/fonts/"

# define ON true
# define OFF false

#endif /* !CONSTANTS_HH_ */
