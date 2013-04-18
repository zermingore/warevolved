bin_PROGRAMS = $(top_srcdir)/we

# Use right g++ flags.
__top_srcdir__we_CPPFLAGS = -W -Wall -Wextra -pedantic	 		\
-Wfloat-equal -Wcast-qual -Wcast-align -Wunreachable-code -Wundef		\
-Wpointer-arith -Wmissing-declarations -Wmissing-braces -Wparentheses 		\
-O0 -DDEBUG -g \
-Wformat -Wwrite-strings # check printf args && const strings


# release:
#  -s -02
# -O3 -DNDEBUG
# -Wshadow

# -Wwrite-strings (check const strings)


#__top_srcdir__we_CPPFLAGS += ${libglfw_CFLAGS} ${GLEW_CFLAGS} ${OPENAL_CFLAGS} ${IMAGE_MAGICK_CFLAGS}
#__top_srcdir__we_LDADD = ${libglfw_LIBS} ${GLEW_LIBS} ${OPENAL_LIBS} ${LIBPQXX_LIBS} ${IMAGE_MAGICK_LIBS}

__top_srcdir__we_SOURCES =	\
main.cc					\
\
core/Context.cc			\
core/GraphicEngine.cc	\
\
common/System.cc		\
common/Settings.cc		\
common/Status.cc		\
\
input/KeyManager.cc		\
input/Event.cc			\
\
game/Game.cc			\
game/Map.cc				\
game/Cursor.cc


# if -DDEBUG __top_srcdir__we_SOURCES += tools/debug_funs

# models/Cube.cc
# models/Shape2D.cc
