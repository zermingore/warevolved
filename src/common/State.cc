#include <common/State.hh>
#include <common/macros.hh>


State::State(mode& mode) :
  _currentMode (mode),
  _menu (nullptr)
{
  // if (CURSOR)
  //   _cursorCoords = CURSOR->coords();
}

State::State(mode mode, std::shared_ptr<Menu> menu) :
  _currentMode (mode),
  _menu (menu)
{
  // if (CURSOR)
  //   _cursorCoords = CURSOR->coords();
}
