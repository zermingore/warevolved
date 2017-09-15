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
#include <resources/Image.hh>
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

  _evtMgr->registerEvent(e_input::MOVE_UP,    [=] { moveUnitUp();    });
  _evtMgr->registerEvent(e_input::MOVE_DOWN,  [=] { moveUnitDown();  });
  _evtMgr->registerEvent(e_input::MOVE_LEFT,  [=] { moveUnitLeft();  });
  _evtMgr->registerEvent(e_input::MOVE_RIGHT, [=] { moveUnitRight(); });

  _evtMgr->registerEvent(e_input::SELECTION,  [=] {
      game::Status::pushState(e_state::ACTION_MENU);

      // giving the next state (action menu) the original unit position
      game::Status::currentState()->setAttributes(std::make_shared<Coords> (_holoUnitPosition));
      game::Status::currentState()->resume();
    });

  _evtMgr->registerEvent(e_input::EXIT, [=] { exit(); });

  // Graphical attributes initialization
  _holoUnit = resources::ResourcesManager::getImage("soldiers"); /// \todo hard-coded soldiers
  _holoUnitSprite = _holoUnit->sprite();
  _holoUnitPosition = player->cursor()->coords();


  using namespace graphics;
  auto x(static_cast<component> (_holoUnitSprite->getTexture()->getSize().x));
  // explicitly using some floats for the division
  float y = static_cast<float> (_holoUnitSprite->getTexture()->getSize().y);
  using p = MapGraphicsProperties;
  _holoUnitSprite->setScale(p::cellWidth() / x, p::cellHeight() / y);

  // Fading sprite at original position
  auto unit(game::Status::battle()->map()->unit(_originalCoords));
  assert(unit);
  unit->sprite()->setColor(Color(255, 255, 255, 160));

  // Path finding
  PathFinding::setOrigin(_originalCoords, unit);
}


StateMovingUnit::~StateMovingUnit()
{
  // could write an assert checking if game::Status::battle() is still valid
  // (to avoid segfault exiting the game while moving a unit)

  auto unit(game::Status::battle()->map()->unit(_originalCoords));

  // if the unit was moved, it is no longer existing at these original coordinates
  if (unit) {
    unit->sprite()->setColor(graphics::Color(255, 255, 255, 255));
  }

  PathFinding::clearPath();
}


void StateMovingUnit::exit()
{
  /// \todo kill the path finding (needed ?)
  game::Status::popCurrentState();
}

void StateMovingUnit::resume()
{
  _nbColumns = game::Status::battle()->map()->nbColumns();
  _nbLines = game::Status::battle()->map()->nbLines();
}


// _________________________  Graphical Units motion ________________________ //
void StateMovingUnit::moveUnitUp()
{
  if (_holoUnitPosition.l > 0 && PathFinding::allowedMove(e_direction::UP))
  {
    --_holoUnitPosition.l;
    PathFinding::addNextDirection(e_direction::UP);
  }
}

void StateMovingUnit::moveUnitDown()
{
  if (_holoUnitPosition.l < _nbLines - 1
      && PathFinding::allowedMove(e_direction::DOWN))
  {
    ++_holoUnitPosition.l;
    PathFinding::addNextDirection(e_direction::DOWN);
  }
}

void StateMovingUnit::moveUnitLeft()
{
  if (_holoUnitPosition.c > 0 && PathFinding::allowedMove(e_direction::LEFT))
  {
    --_holoUnitPosition.c;
    PathFinding::addNextDirection(e_direction::LEFT);
  }
}

void StateMovingUnit::moveUnitRight()
{
  if (_holoUnitPosition.c < _nbColumns - 1
      && PathFinding::allowedMove(e_direction::RIGHT))
  {
    ++_holoUnitPosition.c;
    PathFinding::addNextDirection(e_direction::RIGHT);
  }
}


void StateMovingUnit::draw()
{
  /// \todo should only the graphics engine be allowed to draw ?
  // graphics::GraphicsEngine::draw(_holoUnitSprite);

  PathFinding::highlightCells();
  PathFinding::drawPath();

  _holoUnitSprite->setColor(graphics::Color(255, 127, 127, 255));
  _holoUnit->drawAtCell(_holoUnitPosition);
}
