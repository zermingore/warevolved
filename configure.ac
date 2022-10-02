#                        -*- Autoconf -*-


AC_INIT([ms],[1.0])

AC_CONFIG_AUX_DIR([build-aux])

# forcing c++2a usage (must be before AC_PROG_CXX)
CXXFLAGS="$CXXFLAGS -std=c++2a -pthread"


if [[ -n "$SFML_PATH" ]]
then
CPPFLAGS="$CPPFLAGS -I$SFML_PATH -I$SFML_PATH/include/"
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


AC_ARG_VAR(WE_EXTRA_FLAGS, Compilation flags (for the sources only, not the libraries))

AC_ARG_ENABLE(
  [unit-tests],
  [AS_HELP_STRING([--enable-unit-tests],[Build unit tests])],
  [case "${enableval}" in
     yes)
       unit_tests=true
       AC_CONFIG_LINKS([tests/unit/main.cc:tests/unit/main.cc])
       AC_CONFIG_LINKS([tests/unit/lib/doctest.h:tests/unit/lib/doctest.h])
       ;;
     no)
       unit_tests=false
       ;;
     *)
       AC_MSG_ERROR([Unexpected value ${enableval} for --unit-tests (expected true or false)])
       ;;
  esac],
  [unit_tests=false]
)
AM_CONDITIONAL([UNIT_TESTS], [test x$unit_tests = xtrue])


AC_OUTPUT
