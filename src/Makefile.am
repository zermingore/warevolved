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
graphics/MapGraphicsProperties.cc   \
\
resources/ResourcesManager.cc       \
resources/Resource.cc               \
resources/Image.cc                  \
resources/Font.cc                   \
\
debug/Debug.cc                      \
debug/OSD.cc                        \
debug/EnumPrint.cc                  \
debug/EventsLogger.cc               \
\
common/System.cc                    \
common/Settings.cc                  \
common/Status.cc                    \
\
context/State.cc                    \
context/StateFactory.cc             \
context/StatePlaying.cc             \
context/StateMenu.cc                \
context/StateMovingUnit.cc          \
context/StateSelectTarget.cc        \
\
input/KeyManager.cc                 \
input/EventManager.cc               \
input/InputProcessor.cc             \
\
game/Game.cc                        \
game/Map.cc                         \
game/Cell.cc                        \
game/Battle.cc                      \
game/units/Unit.cc                  \
game/units/UnitFactory.cc           \
game/units/Soldier.cc               \
game/Player.cc                      \
game/PathFinding.cc                 \
\
interface/Interface.cc              \
interface/InterfaceSettings.cc      \
interface/InterfaceElement.cc       \
interface/Cursor.cc                 \
interface/menus/Menu.cc             \
interface/menus/MenuEntry.cc        \
interface/menus/InGameMenu.cc       \
interface/menus/MenuMap.cc          \
interface/menus/MenuAction.cc


# Generated files
__top_srcdir__we_SOURCES +=                     \
generated/enum_print/generated_terrains.cc      \
generated/enum_print/generated_path_shapes.cc   \
generated/enum_print/generated_input.cc         \
generated/enum_print/generated_directions.cc    \
generated/enum_print/generated_attack_result.cc \
generated/enum_print/generated_states.cc        \
generated/enum_print/generated_units.cc
