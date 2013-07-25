bin_PROGRAMS = $(top_srcdir)/we

# Use right g++ flags.
__top_srcdir__we_CPPFLAGS = -W -Wall -Wextra -pedantic			 		\
-Wfloat-equal -Wcast-qual -Wcast-align -Wunreachable-code -Wundef		\
-Wpointer-arith -Wmissing-declarations -Wmissing-braces -Wparentheses	\
-O0 -g -DDEBUG -DDEBUG_LEAKS \
-Wformat -Wwrite-strings # check printf args && const strings


# Advance Debug
# -DDEBUG_XML
# -DEBUG_XML_FULL
# -DDEBUG_PERFS

# release:
#  -s -02
# -O3 -DNDEBUG
# -Wshadow


__top_srcdir__we_SOURCES =		\
main.cc							\
\
core/Context.cc					\
\
graphics/GraphicEngine.cc		\
\
resources/ResourcesManager.cc	\
resources/Resource.cc			\
resources/Image.cc				\
resources/Font.cc				\
\
common/System.cc				\
common/Settings.cc				\
common/Status.cc				\
common/State.cc					\
\
input/KeyManager.cc				\
input/Event.cc					\
\
game/Game.cc					\
game/Map.cc						\
game/Cell.cc					\
game/Unit.cc					\
game/Terrain.cc					\
game/PathFinding.cc				\
\
interface/Interface.cc			\
interface/Cursor.cc				\
interface/menus/EntriesMenu.cc	\
interface/menus/MenuEntry.cc	\
interface/menus/InGameMenu.cc
