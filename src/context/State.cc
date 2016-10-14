#include <context/State.hh>
#include <common/macros.hh>
#include <input/EventManager.hh>
#include <common/enums/input.hh>

#include <common/Debug.hh>


void print()
{
  DEBUG_PRINT("print()");
}

State::State(e_state& state)
  : _currentState (state)
  , _eventManager (nullptr)
{
  // Facto DP
  switch (static_cast<int> (state))
  {
    DEBUG_PRINT("State: current state");
    DEBUG_PRINT_VALUE(static_cast<int> (state));
    default:
      DEBUG_PRINT("UNRECOGNIZED STATE. Unable to instantiate an EventManager");
      _eventManager = std::make_shared<EventManager> ();
      _eventManager->registerEvent(e_input::MOVE_LEFT_1, print);
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
}
