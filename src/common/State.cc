#include <common/State.hh>
#include <common/macros.hh>
#include <input/EventManager.hh>


State::State(e_mode& mode) :
  _currentMode (mode),
  _menu (nullptr),
  _eventManager (nullptr)
{
  // if (CURSOR)
  //   _cursorCoords = CURSOR->coords();


  switch (static_cast<int> (mode))
  {
    default:
      _eventManager = std::make_shared<EventManager> ();
      break;
 //   MAIN_MENU,
  //     IN_GAME,
  //     PLAYING,

  // SELECTION_MENU, // pick a Unit
  // MOVING_UNIT, // move it
  // ACTION_MENU, // give it an order
  // ATTACK, // ask a Unit to attack

  // LOADING,
  // SAVING,

  // READ_TEXTBOX,
  // WRITE_MESSAGE


  //   default:
  //   static_assert("invalid mode");
      }


//  _eventManager->registerEvent("cursor right", Cursor::moveRight());
}

State::State(e_mode mode,
             std::shared_ptr<Menu> menu) :
  _currentMode (mode),
  _menu (menu)
{


  // if (CURSOR)
  //   _cursorCoords = CURSOR->coords();
}
