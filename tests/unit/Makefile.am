check_PROGRAMS = check_we
TESTS = ${check_PROGRAMS}

# Link against pugixml
check_we_LDADD  = ${abs_top_builddir}/lib/libpugixml.a
check_we_LDADD += -lstdc++fs # filesystem

# Setting the __top_srcdir__we_CXXFLAGS variable
__top_srcdir__check_we_CXXFLAGS = -I${abs_top_builddir}/lib/

# Source files
__top_srcdir__we_SOURCES =               \
${srcdir}/../../src/graphics/GraphicsEngine.cc               \
${srcdir}/../../src/graphics/Context.cc                      \
${srcdir}/../../src/graphics/Properties.cc                   \
${srcdir}/../../src/graphics/Sprite.cc                       \
\
${srcdir}/../../src/resources/ResourcesManager.cc            \
${srcdir}/../../src/resources/Font.cc                        \
${srcdir}/../../src/resources/Text.cc                        \
\
${srcdir}/../../src/debug/Debug.cc                           \
${srcdir}/../../src/debug/OSD.cc                             \
\
${srcdir}/../../src/config/Settings.cc                       \
\
${srcdir}/../../src/context/State.cc                         \
${srcdir}/../../src/context/StateGlobal.cc                   \
${srcdir}/../../src/context/StatesFactory.cc                 \
${srcdir}/../../src/context/StatePlaying.cc                  \
${srcdir}/../../src/context/StateEditMap.cc                  \
${srcdir}/../../src/context/StateMenu.cc                     \
${srcdir}/../../src/context/StateMenu2d.cc                   \
${srcdir}/../../src/context/StateMovingUnit.cc               \
${srcdir}/../../src/context/StateSelectCell.cc               \
${srcdir}/../../src/context/StateSelectTarget.cc             \
${srcdir}/../../src/context/StateSelectDropZone.cc           \
${srcdir}/../../src/context/StateSelectExitZone.cc           \
${srcdir}/../../src/context/StateInventory.cc                \
\
${srcdir}/../../src/input/KeyManager.cc                      \
${srcdir}/../../src/input/ReplayManager.cc                   \
${srcdir}/../../src/input/EventManager.cc                    \
${srcdir}/../../src/input/EventsProcessor.cc                 \
${srcdir}/../../src/input/InputsListener.cc                  \
\
${srcdir}/../../src/game/Game.cc                             \
${srcdir}/../../src/game/Status.cc                           \
${srcdir}/../../src/game/Battle.cc                           \
${srcdir}/../../src/game/Map.cc                              \
${srcdir}/../../src/game/Terrain.cc                          \
${srcdir}/../../src/game/TerrainsHandler.cc                  \
${srcdir}/../../src/game/units/Unit.cc                       \
${srcdir}/../../src/game/units/UnitsFactory.cc               \
${srcdir}/../../src/game/units/Vehicle.cc                    \
${srcdir}/../../src/game/units/Car.cc                        \
${srcdir}/../../src/game/units/Motorcycle.cc                 \
${srcdir}/../../src/game/units/Soldier.cc                    \
${srcdir}/../../src/game/Player.cc                           \
${srcdir}/../../src/game/PathFinding.cc                      \
${srcdir}/../../src/game/Building.cc                         \
${srcdir}/../../src/game/Inventory.cc                        \
${srcdir}/../../src/game/ItemsContainer.cc                   \
${srcdir}/../../src/game/Item.cc                             \
\
${srcdir}/../../src/interface/Interface.cc                   \
${srcdir}/../../src/interface/InterfaceElement.cc            \
${srcdir}/../../src/interface/Cursor.cc                      \
${srcdir}/../../src/interface/Panel.cc                       \
${srcdir}/../../src/interface/MiniMap.cc                     \
${srcdir}/../../src/interface/menus/Menu.cc                  \
${srcdir}/../../src/interface/menus/MenuEntry.cc             \
${srcdir}/../../src/interface/menus/InGameMenu.cc            \
${srcdir}/../../src/interface/menus/MenuMap.cc               \
${srcdir}/../../src/interface/menus/MenuAction.cc            \
${srcdir}/../../src/interface/menus/MenuCrew.cc              \
${srcdir}/../../src/interface/menus/MenuBuilding.cc          \
\
${srcdir}/../../src/tools/StringParser.cc                    \
${srcdir}/../../src/tools/Fps.cc                             \
${srcdir}/../../src/tools/Random.cc                          \
${srcdir}/../../src/tools/options/Option.cc                  \
${srcdir}/../../src/tools/options/OptionsParser.cc

# Generated sources files
__top_srcdir__we_SOURCES +=          \
  ${srcdir}/../../src/generated/enum_print/enum_print.cc


# include ${top_srcdir}/src/Makefile.am

check_we_SOURCES = ${top_builddir}/tests/unit/main.cc ${top_builddir}/tests/unit/lib/doctest.h ${__top_srcdir__we_SOURCES}

check_we_CXXFLAGS = -I${abs_top_builddir}/tests/unit/lib/ -I${srcdir}/../../src/ -I${srcdir}/../../src/lib/ -I${abs_top_builddir}/lib/
