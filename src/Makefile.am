# TODO multi-folders ?
# SUBDIRS = core common media tools entities/character/ entities/bodyparts/ items items/clothes db input globals tools


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


__top_srcdir__we_CPPFLAGS += ${libglfw_CFLAGS} ${GLEW_CFLAGS} ${OPENAL_CFLAGS} ${IMAGE_MAGICK_CFLAGS}
__top_srcdir__we_LDADD = ${libglfw_LIBS} ${GLEW_LIBS} ${OPENAL_LIBS} ${LIBPQXX_LIBS} ${IMAGE_MAGICK_LIBS}

__top_srcdir__we_SOURCES =	\
main.cc					\
\
core/Context.cc			\
core/Game.cc			\
core/GraphicEngine.cc	\
\
common/System.cc		\
common/Settings.cc		\
\
tools/Cursor.cc			#\
\
graphics/Texture.cc		\
graphics/TextureManager.cc	\
graphics/Skybox.cc		\
graphics/Light.cc		\
graphics/DirectionalLight.cc	\
\
db/DBManager.cc			\
db/DBInventory.cc		\
\
entities/character/Character.cc	\
entities/bodyparts/BodyPart.cc	\
\
globals/keys.c			\
globals/engines.cc		\
\
input/Input.cc			\
input/InputCharacter.cc		\
\
items/Item.cc			\
items/clothes/Cloth.cc		\
\
media/Shader.cc			\
media/Sound.cc			\
\
tools/Vector.cc			\
tools/Matrix.cc			\
\
tools/debug_funs.cc


# if -DDEBUG __top_srcdir__we_SOURCES += tools/debug_funs

# models/Cube.cc
# models/Shape2D.cc
