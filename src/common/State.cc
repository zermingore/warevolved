#include <common/State.hh>
#include <common/macros.hh>
#include <input/EventManager.hh>
#include <input/MapEventManager.hh>

#include <common/Debug.hh>

State::State(e_mode& mode)
  : _currentMode (mode)
  , _menu (nullptr)
  , _eventManager (nullptr)
{
  // if (CURSOR)
  //   _cursorCoords = CURSOR->coords();

  // Facto DP
  switch (static_cast<int> (mode))
  {
    DEBUG_PRINT("State: current mode");
    DEBUG_PRINT_VALUE(static_cast<int> (mode));
    default:
      DEBUG_PRINT("Unrecognized mode -> unable to instantiate an EventManager");
      DEBUG_PRINT("Picking MapEventManager");
      _eventManager = std::make_shared<EventManager> ();
      break;
  //   MAIN_MENU,
  //     IN_GAME,
  //     PLAYING,

  // SELECTION_MENU, // pick a Unit
  // MOVING_UNIT, // move it
  // ACTION_MENU, // give it an order
  // ATTACK, // ask a Unit to attack
  //   default:
  //   static_assert("invalid mode");
  }

  //  _eventManager->registerEvent("cursor right", Cursor::moveRight());
}

State::State(e_mode mode, std::shared_ptr<Menu> menu)
  : _currentMode (mode)
  , _menu (menu)
{
  // if (CURSOR)
  //   _cursorCoords = CURSOR->coords();
}
