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


StateMovingUnit::StateMovingUnit()
  : State()
  , _originalCoords(Status::interface()->element("cursor")->coords())
{
  // used to get the cursor's coordinates and access to the callbacks
  auto player(Status::player());

  if (!player->updateSelectedUnit())
  {
    ERROR("Unable to set selected unit");
    // abort / exit mode ?
  }

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
//  graphics::GraphicsEngine::draw(_holoUnit);

  auto p(Status::battle()->map()->graphicsProperties());

  /// \todo set sprite accordingly to the unis at original coordinates
  graphics::Image& image(resources::ResourcesManager::getImage("soldiers"));

  float x = image.sprite()->getTexture()->getSize().x;
  float y = image.sprite()->getTexture()->getSize().y;
  image.sprite()->setScale(p->cellWidth() / x, p->cellHeight() / y);

# ifdef DEBUG
  // we suppose the sprite is always larger than the cell
  if (x < p->cellWidth() || y < p->cellHeight()) {
    ERROR("Sprite scale failure");
  }
# endif

  /// \todo own sprite, not a copy (or else affect every sprite...)
  image.sprite()->setColor(sf::Color(127, 127, 127, 100));

  image.drawAtCell(_holoUnitPosition, p);
}
