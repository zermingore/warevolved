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
    Debug::error("Unable to set selected unit");
    // abort / exit mode ?
  }

  _evtMgr->registerEvent(e_input::MOVE_UP_1,    [=] { moveUnitUp();    });
  _evtMgr->registerEvent(e_input::MOVE_DOWN_1,  [=] { moveUnitDown();  });
  _evtMgr->registerEvent(e_input::MOVE_LEFT_1,  [=] { moveUnitLeft();  });
  _evtMgr->registerEvent(e_input::MOVE_RIGHT_1, [=] { moveUnitRight(); });

  _evtMgr->registerEvent(e_input::SELECTION_1,  [=] {
//      player->validateMoveUnit();
      Status::pushState(e_state::ACTION_MENU);
    });

  _evtMgr->registerEvent(e_input::EXIT_1, [=] {
      exit();
//      Status::interface()->popMenu();
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

}

void StateMovingUnit::moveUnitLeft() {

}

void StateMovingUnit::moveUnitRight() {
  ++_holoUnitPosition.x;
}
