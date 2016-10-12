bin_PROGRAMS = $(top_srcdir)/we

# Use right g++ flags.
# Debug Flags (no optimization, debug symbols, defines)
__top_srcdir__we_CPPFLAGS = -W -Wall -Wextra -pedantic                \
-Wfloat-equal -Wcast-qual -Wcast-align -Wunreachable-code -Wundef     \
-Wpointer-arith -Wmissing-declarations -Wmissing-braces -Wparentheses \
-O0 -g3 -ggdb3 -DDEBUG -DDEBUG_LEAKS \
-Wformat -Wwrite-strings # check printf args && const strings

# export GLIBCXX_FORCE_NEW

# Advance Debug
# -DDEBUG_XML
# -DEBUG_XML_FULL
# -DDEBUG_PERFS

# release:
#  -s -02
# -O3 -DNDEBUG
# -Wshadow


__top_srcdir__we_SOURCES =          \
main.cc                             \
\
pugixml/pugixml.cpp                 \
\
core/Context.cc                     \
\
graphics/GraphicsEngine.cc          \
\
resources/ResourcesManager.cc       \
resources/Resource.cc               \
resources/Image.cc                  \
resources/Font.cc                   \
\
common/Debug.cc                     \
common/System.cc                    \
common/Settings.cc                  \
common/Status.cc                    \
common/State.cc                     \
\
input/KeyManager.cc                 \
input/EventManager.cc               \
input/InputProcessor.cc             \
\
game/Game.cc                        \
game/Map.cc                         \
game/Cell.cc                        \
game/applications/Battle.cc         \
game/units/Unit.cc                  \
game/units/Soldier.cc               \
game/PathFinding.cc                 \
game/Player.cc                      \
\
interface/Interface.cc              \
interface/InterfaceSettings.cc      \
interface/Cursor.cc                 \
interface/menus/Menu.cc             \
interface/menus/MenuEntry.cc        \
interface/InterfaceElement.cc       \
interface/menus/InGameMenu.cc
