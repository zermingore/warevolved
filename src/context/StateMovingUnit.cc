#include <context/StateMovingUnit.hh>
#include <input/EventManager.hh>
#include <common/enums/input.hh>
#include <common/Status.hh>
#include <game/Player.hh>
#include <common/enums/states.hh>
#include <interface/menus/InGameMenu.hh>
#include <graphics/GraphicsEngine.hh>
#include <graphics/MapGraphicsProperties.hh>
#include <game/applications/Battle.hh>
#include <resources/Image.hh>
#include <interface/Cursor.hh>
#include <game/units/Unit.hh>
#include <game/PathFinding.hh>
#include <common/enums/directions.hh>



StateMovingUnit::StateMovingUnit()
  : State()
  , _originalCoords(Status::interface()->element("cursor")->coords())
{
  // used to get the cursor's coordinates and access to the callbacks
  auto player(Status::player());

  // we need a selected unit to continue
  assert(player->updateSelectedUnit());

  _evtMgr->registerEvent(e_input::MOVE_UP_1,    [=] { moveUnitUp();    });
  _evtMgr->registerEvent(e_input::MOVE_DOWN_1,  [=] { moveUnitDown();  });
  _evtMgr->registerEvent(e_input::MOVE_LEFT_1,  [=] { moveUnitLeft();  });
  _evtMgr->registerEvent(e_input::MOVE_RIGHT_1, [=] { moveUnitRight(); });

  _evtMgr->registerEvent(e_input::SELECTION_1,  [=] {
      Status::pushState(e_state::ACTION_MENU);

      // giving the next state (action menu) the original unit position
      Status::currentState()->setAttributes(std::make_shared<Coords> (_holoUnitPosition));
      Status::currentState()->resume();
    });

  _evtMgr->registerEvent(e_input::EXIT_1, [=] {
      exit();
    });

  // Graphical attributes initialization
  _holoUnit = resources::ResourcesManager::getImage("soldiers"); /// \todo hard-coded soldiers
  _holoUnitSprite = _holoUnit->sprite();
  _holoUnitPosition = player->cursor()->coords();

  // explicitly using some floats for the division
  float x = _holoUnitSprite->getTexture()->getSize().x;
  float y = _holoUnitSprite->getTexture()->getSize().y;
  using p = graphics::MapGraphicsProperties;
  _holoUnitSprite->setScale(p::cellWidth() / x, p::cellHeight() / y);

  // Fading sprite at original position
  auto unit(Status::battle()->map()->unit(_originalCoords));
  assert(unit);
  unit->sprite()->setColor(sf::Color(255, 255, 255, 160));

  // Path finding
  PathFinding::setOrigin(_originalCoords, unit);
}


StateMovingUnit::~StateMovingUnit()
{
  auto unit(Status::battle()->map()->unit(_originalCoords));

  // if the unit was moved, it is no longer existing at these original coordinates
  if (unit) {
    unit->sprite()->setColor(sf::Color(255, 255, 255, 255));
  }

  PathFinding::clearPath();
}


void StateMovingUnit::exit()
{
  /// \todo kill the path finding (needed ?)
  Status::popCurrentState();
}

void StateMovingUnit::resume()
{
  _nbColumns = Status::battle()->map()->nbColumns();
  _nbLines = Status::battle()->map()->nbLines();
}


// _________________________  Graphical Units motion ________________________ //
void StateMovingUnit::moveUnitUp()
{
  if (_holoUnitPosition.l > 0 && PathFinding::allowedMove())
  {
    --_holoUnitPosition.l;
    PathFinding::addNextDirection(e_direction::UP);
  }
}

void StateMovingUnit::moveUnitDown()
{
  if (_holoUnitPosition.l < _nbLines - 1 && PathFinding::allowedMove())
  {
    ++_holoUnitPosition.l;
    PathFinding::addNextDirection(e_direction::DOWN);
  }
}

void StateMovingUnit::moveUnitLeft()
{
  if (_holoUnitPosition.c > 0 && PathFinding::allowedMove())
  {
    --_holoUnitPosition.c;
    PathFinding::addNextDirection(e_direction::LEFT);
  }
}

void StateMovingUnit::moveUnitRight()
{
  if (_holoUnitPosition.c < _nbColumns - 1 && PathFinding::allowedMove())
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

  _holoUnitSprite->setColor(sf::Color(255, 127, 127, 255));
  _holoUnit->drawAtCell(_holoUnitPosition);
}
