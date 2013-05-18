bin_PROGRAMS = $(top_srcdir)/we

# Use right g++ flags.
__top_srcdir__we_CPPFLAGS = -W -Wall -Wextra -pedantic	 		\
-Wfloat-equal -Wcast-qual -Wcast-align -Wunreachable-code -Wundef		\
-Wpointer-arith -Wmissing-declarations -Wmissing-braces -Wparentheses 		\
-O0 -g -DDEBUG -DDEBUG_XML -DDEBUG_LEAKS -DDEBUG_PERFS \
-Wformat -Wwrite-strings # check printf args && const strings


# release:
#  -s -02
# -O3 -DNDEBUG
# -Wshadow

# -Wwrite-strings (check const strings)


#__top_srcdir__we_CPPFLAGS += ${libglfw_CFLAGS} ${GLEW_CFLAGS} ${OPENAL_CFLAGS} ${IMAGE_MAGICK_CFLAGS}
#__top_srcdir__we_LDADD = ${libglfw_LIBS} ${GLEW_LIBS} ${OPENAL_LIBS} ${LIBPQXX_LIBS} ${IMAGE_MAGICK_LIBS}

__top_srcdir__we_SOURCES =		\
main.cc							\
\
core/Context.cc					\
\
graphics/GraphicEngine.cc		\
graphics/SelectionMenu.cc		\
\
resources/ResourcesManager.cc	\
resources/Resource.cc			\
resources/Image.cc				\
resources/Font.cc				\
\
common/System.cc				\
common/Settings.cc				\
common/Status.cc				\
\
input/KeyManager.cc				\
input/Event.cc					\
\
game/Game.cc					\
game/Map.cc						\
game/Cell.cc					\
game/Cursor.cc					\
game/Unit.cc					\
game/Terrain.cc



# if -DDEBUG __top_srcdir__we_SOURCES += tools/debug_funs
