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
  , _menu (nullptr)
  , _eventManager (nullptr)
{
  // if (CURSOR)
  //   _cursorCoords = CURSOR->coords();

  // Facto DP
  switch (static_cast<int> (state))
  {
    DEBUG_PRINT("State: current state");
    DEBUG_PRINT_VALUE(static_cast<int> (state));
    default:
      DEBUG_PRINT("Unrecognized state -> unable to instantiate an EventManager");
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

State::State(e_state state, std::shared_ptr<Menu> menu)
  : _currentState (state)
  , _menu (menu)
{
  // if (CURSOR)
  //   _cursorCoords = CURSOR->coords();
}
