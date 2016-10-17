#include <context/StateFactory.hh>
#include <context/StatePlaying.hh>
#include <input/EventManager.hh>

#include <common/Debug.hh>


std::shared_ptr<State> StateFactory::createState(e_state& state)
{
  DEBUG_PRINT("ILLEGAL CALL to abstract class State ?");
  DEBUG_PRINT("State: current state");
  DEBUG_PRINT_VALUE(static_cast<int> (state));

  // Facto DP
  switch (state)
  {
    case e_state::PLAYING:
      return std::make_shared<StatePlaying> ();

    default:
      DEBUG_PRINT("UNRECOGNIZED STATE. Unable to instantiate an EventManager");
      break;
  //   MAIN_MENU,
  //     IN_GAME,
  //     PLAYING,

  // SELECTION_MENU, // pick a Unit
  // MOVING_UNIT, // move it
  // ACTION_MENU, // give it an order
  // ATTACK, // ask a Unit to attack
  //   default:
  //   static_assert("invalid state");
  }

  //  _eventManager->registerEvent("cursor right", Cursor::moveRight());


  // never reached
  return nullptr;
}
