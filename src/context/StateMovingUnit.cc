#include <context/StateMovingUnit.hh>

#include <cassert>

#include <input/EventManager.hh>
#include <common/enums/input.hh>
#include <game/Status.hh>
#include <common/enums/states.hh>
#include <common/enums/directions.hh>
#include <interface/Interface.hh>
#include <interface/Cursor.hh>
#include <interface/menus/InGameMenu.hh>
#include <graphics/graphic_types.hh>
#include <graphics/GraphicsEngine.hh>
#include <graphics/MapGraphicsProperties.hh>
#include <graphics/Sprite.hh>
#include <game/Battle.hh>
#include <game/Player.hh>
#include <game/units/Unit.hh>
#include <game/PathFinding.hh>



StateMovingUnit::StateMovingUnit()
  : State()
  , _originalCoords(game::Status::interface()->element("cursor")->coords())
{
  // used to get the cursor's coordinates and access to the callbacks
  auto player(game::Status::player());

  // we need a selected unit to continue
  player->updateSelectedUnit();

  _evtMgr->registerEvent(e_input::MOVE_UP,    [=, this] { moveUnitUp();    });
  _evtMgr->registerEvent(e_input::MOVE_DOWN,  [=, this] { moveUnitDown();  });
  _evtMgr->registerEvent(e_input::MOVE_LEFT,  [=, this] { moveUnitLeft();  });
  _evtMgr->registerEvent(e_input::MOVE_RIGHT, [=, this] { moveUnitRight(); });

  _evtMgr->registerEvent(e_input::SELECTION,  [=, this] {
      game::Status::pushState(e_state::ACTION_MENU);

      // giving the next state (action menu) the original unit position
      game::Status::setStateAttributes(
        std::make_shared<Coords> (_holoUnitPosition));
      game::Status::resumeState();
    });

  _evtMgr->registerEvent(e_input::EXIT, [=, this] { exit(); });

  // Graphical attributes initialization
  auto map { game::Status::battle()->map() };
  auto cursor_coords { player->cursor()->coords() };

  // Make a deep-copy of the Unit's Sprite
  _holoUnit = std::make_unique<graphics::Sprite> (
    *map->unit(cursor_coords)->sprite());
  _holoUnitPosition = cursor_coords;
  player->setCellCursorPosition(cursor_coords);

  const auto x { static_cast<graphics::component> (_holoUnit->size().x) };
  const auto y { static_cast<graphics::component> (_holoUnit->size().y) };
  using p = graphics::MapGraphicsProperties;
  _holoUnit->setScale(p::cellWidth() / x, p::cellHeight() / y);

  // Fading sprite at original position
  auto unit(map->unit(_originalCoords));
  assert(unit);
  unit->setColor({ 255, 0, 0, 255 });

  _pathFinding = std::make_unique<PathFinding> (unit);
}



StateMovingUnit::~StateMovingUnit()
{
  // could write an assert checking if game::Status::battle() is still valid
  // (to avoid segfault exiting the game while moving a unit)

  _pathFinding->hideAllowedPath();
  auto unit(game::Status::battle()->map()->unit(_originalCoords));
  if (unit) {
    unit->setColor({ 255, 255, 255, 255 });
  }
}



void StateMovingUnit::exit()
{
  _pathFinding->hideAllowedPath();
  game::Status::popCurrentState();
  game::Status::player()->resetCellCursorPosition();
}



void StateMovingUnit::resume()
{
  _nbColumns = game::Status::battle()->map()->nbColumns();
  _nbLines = game::Status::battle()->map()->nbLines();
}


// _________________________  Graphical Units motion ________________________ //
void StateMovingUnit::moveUnitUp()
{
  if (_holoUnitPosition.l > 0 && _pathFinding->allowedMove(e_direction::UP))
  {
    --_holoUnitPosition.l;
    game::Status::player()->setCellCursorPosition(_holoUnitPosition);
    _pathFinding->addNextDirection(e_direction::UP);
  }
}

void StateMovingUnit::moveUnitDown()
{
  if (_holoUnitPosition.l < _nbLines - 1
      && _pathFinding->allowedMove(e_direction::DOWN))
  {
    ++_holoUnitPosition.l;
    game::Status::player()->setCellCursorPosition(_holoUnitPosition);
    _pathFinding->addNextDirection(e_direction::DOWN);
  }
}

void StateMovingUnit::moveUnitLeft()
{
  if (_holoUnitPosition.c > 0 && _pathFinding->allowedMove(e_direction::LEFT))
  {
    --_holoUnitPosition.c;
    game::Status::player()->setCellCursorPosition(_holoUnitPosition);
    _pathFinding->addNextDirection(e_direction::LEFT);
  }
}

void StateMovingUnit::moveUnitRight()
{
  if (_holoUnitPosition.c < _nbColumns - 1
      && _pathFinding->allowedMove(e_direction::RIGHT))
  {
    ++_holoUnitPosition.c;
    game::Status::player()->setCellCursorPosition(_holoUnitPosition);
    _pathFinding->addNextDirection(e_direction::RIGHT);
  }
}


void StateMovingUnit::draw()
{
  /// \todo should only the graphics engine be allowed to draw ?
  // graphics::GraphicsEngine::draw(_holoUnit);

  _pathFinding->highlightCells();
  _pathFinding->drawPath();

  _holoUnit->setColor({ 255, 127, 127, 255 });
  _holoUnit->drawAtCell(_holoUnitPosition);
}
