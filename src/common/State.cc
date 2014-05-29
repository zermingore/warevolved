#include <common/State.hh>
#include <common/macros.hh>
#include <common/globals.hh>


State::State(e_mode mode) :
  _mode (mode),
  _menu (nullptr)
{
  if (CURSOR)
    _cursorCoords = CURSOR->coords();
}


State::State(e_mode mode, EntriesMenu *menu) :
  _mode (mode),
  _menu (menu)
{
  if (CURSOR)
    _cursorCoords = CURSOR->coords();
}
