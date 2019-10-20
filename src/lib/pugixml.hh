/**
 * \file
 * \brief Pugixml inclusion wrapper,
 * used to disable some specific compiler flags
 */

#ifndef LIB_PUGIXML_HH_
# define LIB_PUGIXML_HH_

# pragma GCC diagnostic push
#  pragma GCC diagnostic ignored "-Wsuggest-override"
#  pragma GCC diagnostic ignored "-Wlong-long"
#  pragma GCC diagnostic ignored "-Weffc++"
#  pragma GCC diagnostic ignored "-Wzero-as-null-pointer-constant"
#  include <pugixml/pugixml.hpp>
# pragma GCC diagnostic pop

#endif /* !LIB_PUGIXML_HH_ */
