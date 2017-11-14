#                        -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_INIT([ms], [1.0])

AC_CONFIG_AUX_DIR([build-aux])

# forcing c++17 usage (must be before AC_PROG_CXX)
CXXFLAGS="$CXXFLAGS -std=c++1z -pthread"


if [[ -n "$SFML_PATH" ]]
then
CPPFLAGS="$CPPFLAGS -I$SFML_PATH -I$SFML_PATH/include/"
else
SFML_PATH=""
fi

# Automake.
AM_INIT_AUTOMAKE([subdir-objects color-tests -Wall -Werror foreign])

# By default, let "make" hide the compilation command and display a
# "GEN ..." message, unless V=1 is passed to "make".
AM_SILENT_RULES([yes])

# Checks for programs.
# clang++ is no longer fully supported (as some g++ specific flags are used)
# one can use clang++ deactivating these specific flags in src/Makefile.am
AC_PROG_CXX([g++ clang++])


# Silence warning "ar: 'u' modifier ignored since 'D' is the default"
AC_SUBST(ARFLAGS, [cr])

# use ranlib and ar to build the pugixml library
AC_PROG_RANLIB
AM_PROG_AR


# Checks for typedefs, structures, and compiler characteristics.
# AC_HEADER_STDBOOL6
# AC_C_INLINE

# Checks for library functions.
AC_FUNC_ERROR_AT_LINE


AC_LANG_PUSH([C++])

AC_CHECK_LIB([X11], [main], ,
AC_MSG_ERROR([Unable to find X11 library]))

AC_CHECK_LIB([sfml-system], [main], ,
AC_MSG_ERROR([Unable to find SFML System]))
AC_CHECK_HEADERS([SFML/System.hpp], ,
AC_MSG_ERROR([SFML System headers not found]))

AC_CHECK_LIB([sfml-window], [main], ,
AC_MSG_ERROR([Unable to find SFML Window]))
AC_CHECK_HEADERS([SFML/Window.hpp], ,
AC_MSG_ERROR([SFML Window headers not found]))

AC_CHECK_LIB([sfml-graphics], [main], ,
AC_MSG_ERROR([Unable to find SFML Graphics]))
AC_CHECK_HEADERS([SFML/Graphics.hpp], ,
AC_MSG_ERROR([SFML Graphics headers not found]))

AC_LANG_POP([C++])


AC_CONFIG_FILES([Makefile lib/Makefile src/Makefile]) # check/Makefile

# Link or copy pugixml headers in the build folder
AC_CONFIG_LINKS([lib/pugixml/pugixml.hpp:lib/pugixml/pugixml.hpp])
AC_CONFIG_LINKS([lib/pugixml/pugiconfig.hpp:lib/pugixml/pugiconfig.hpp])

# PKG_CHECK_MODULES([lsfmlwindow], [lsfml-window]) #-lsfml-graphics -lsfml-window -lsfml-system

AC_OUTPUT
