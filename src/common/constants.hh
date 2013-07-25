#ifndef CONSTANTS_HH_
# define CONSTANTS_HH_

# ifdef __unix__
#   define FOLDER_DELIMITER '/'
# else
#   define FOLDER_DELIMITER '\\'
# endif

# define ON true
# define OFF false

// float equality test
# define EPSILON 0.000001

#endif /* !CONSTANTS_HH_ */
