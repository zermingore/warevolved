#include <context/StateMovingUnit.hh>
#include <input/EventManager.hh>
#include <common/enums/input.hh>
#include <common/Status.hh>
#include <game/Player.hh>
#include <common/enums/states.hh>
#include <interface/menus/InGameMenu.hh>
#include <graphics/GraphicsEngine.hh>
#include <game/applications/Battle.hh>
#include <resources/Image.hh>
#include <interface/Cursor.hh>


StateMovingUnit::StateMovingUnit()
  : State()
  , _originalCoords(Status::interface()->element("cursor")->coords())
{
  // used to get the cursor's coordinates and access to the callbacks
  auto player(Status::player());

  // we need a selected unit to continue
  assert(player->updateSelectedUnit());

  _holoUnitPosition = player->cursor()->coords();

  _evtMgr->registerEvent(e_input::MOVE_UP_1,    [=] { moveUnitUp();    });
  _evtMgr->registerEvent(e_input::MOVE_DOWN_1,  [=] { moveUnitDown();  });
  _evtMgr->registerEvent(e_input::MOVE_LEFT_1,  [=] { moveUnitLeft();  });
  _evtMgr->registerEvent(e_input::MOVE_RIGHT_1, [=] { moveUnitRight(); });

  _evtMgr->registerEvent(e_input::SELECTION_1,  [=] {
      PRINTF("selection in MovingUnit:", _holoUnitPosition.x, _holoUnitPosition.y);
      Status::pushState(e_state::ACTION_MENU);

      // giving the next state (action menu) the original unit position
      Status::currentState()->setAttributes(std::make_shared<Coords> (_holoUnitPosition));
    });

  _evtMgr->registerEvent(e_input::EXIT_1, [=] {
      exit();
    });


  // Graphical attributes initialization
  _mapGraphicProperties = Status::battle()->map()->graphicsProperties();
  _holoUnit = resources::ResourcesManager::getImage("soldiers");
  _holoUnitSprite = _holoUnit->sprite();

  // explicitly using some floats for the division
  float x = _holoUnitSprite->getTexture()->getSize().x;
  float y = _holoUnitSprite->getTexture()->getSize().y;
  _holoUnitSprite->setScale(_mapGraphicProperties->cellWidth()  / x,
                            _mapGraphicProperties->cellHeight() / y);
}


void StateMovingUnit::exit()
{
  /// \todo kill the path finding (needed ?)
  Status::popCurrentState();
}



// _________________________  Graphical Units motion ________________________ //
void StateMovingUnit::moveUnitUp() {
  --_holoUnitPosition.y;
}

void StateMovingUnit::moveUnitDown() {
  ++_holoUnitPosition.y;
}

void StateMovingUnit::moveUnitLeft() {
  --_holoUnitPosition.x;
}

void StateMovingUnit::moveUnitRight() {
  ++_holoUnitPosition.x;
}


void StateMovingUnit::draw()
{
  _holoUnitSprite->setColor(sf::Color(255, 127, 127, 255));
  _holoUnit->drawAtCell(_holoUnitPosition, _mapGraphicProperties);

  /// \todo should only the graphics engine be allowed to draw ?
  // graphics::GraphicsEngine::draw(_holoUnitSprite);
}
