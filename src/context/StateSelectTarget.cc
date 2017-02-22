#include <context/StateSelectTarget.hh>
#include <common/enums/input.hh>
#include <input/EventManager.hh>
#include <common/Status.hh>
#include <game/applications/Battle.hh>
#include <game/Map.hh>


StateSelectTarget::StateSelectTarget()
  : State()
{
  _evtMgr->registerEvent(e_input::MOVE_UP_1,    [=] { selectNextTarget();     });
  _evtMgr->registerEvent(e_input::MOVE_DOWN_1,  [=] { selectPreviousTarget(); });
  _evtMgr->registerEvent(e_input::MOVE_LEFT_1,  [=] { selectPreviousTarget(); });
  _evtMgr->registerEvent(e_input::MOVE_RIGHT_1, [=] { selectNextTarget();     });
  _evtMgr->registerEvent(e_input::SELECTION_1,  [=] { validate();             });
  _evtMgr->registerEvent(e_input::EXIT_1,       [=] { exit();                 });
}



// void StateSelectTarget::resume();

void StateSelectTarget::draw()
{
  NOTICE("StateSelectTarget::draw()");
//  _path->showAllowedPath();
//  _path->drawPath();
}


// void StateSelectTarget::fetchAttributes() final;


void StateSelectTarget::selectPreviousTarget()
{
}


void StateSelectTarget::selectNextTarget()
{
}


void StateSelectTarget::validate()
{
  /// \todo add a state to select a target from the path finding
  NOTICE("validate");


  /// \todo give also coordinates of the holo unit (from where it attacks)
  //Status::battle()->map()->attack(target);
  Status::clearStates();
}


void StateSelectTarget::exit()
{
  Status::popCurrentState();
}
