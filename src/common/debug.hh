/*
 * debug.hh
 *
 *  Created on: Jul 23, 2013
 *      Author: zermingore
 */

#ifndef DEBUG_HH_
# define DEBUG_HH_

# ifdef DEBUG
#   define DEBUG_PRINT(x) do { \
      std::cout << x << std::endl; \
    } while (0)
# else
#   define DEBUG_PRINT(x) do { \
    } while (0)
# endif


# ifdef DEBUG
#   define DEBUG_PRINT_VALUE(x) do { \
      std::cout << #x << ": " << x << std::endl; \
    } while (0)
# else
#   define DEBUG_PRINT_VALUE(x) do { \
    } while (0)
# endif



#endif /* !DEBUG_HH_ */
