#include <context/StateMovingUnit.hh>
#include <input/EventManager.hh>
#include <common/enums/input.hh>
#include <common/Status.hh>
#include <game/Player.hh>
#include <common/enums/states.hh>
#include <interface/menus/InGameMenu.hh>



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
  ++_holoUnitPosition.y;
}

void StateMovingUnit::moveUnitDown() {
  --_holoUnitPosition.y;
}

void StateMovingUnit::moveUnitLeft() {
  --_holoUnitPosition.x;
}

void StateMovingUnit::moveUnitRight() {
  ++_holoUnitPosition.x;
}
