#include <common/State.hh>
#include <common/macros.hh>
#include <common/globals.hh>


State::State(e_mode& mode) :
  _mode (mode),
  _menu (nullptr)
{
  PRINTF("State Ctor:", this);

  if (CURSOR)
    _cursorCoords = CURSOR->coords();
}

State::~State()
{
  PRINTF("State Dtor:", this);
}

State::State(e_mode mode, EntriesMenu *menu) :
  _mode (mode),
  _menu (menu)
{
  PRINTF("State Ctor dual args:", this);

  if (CURSOR)
    _cursorCoords = CURSOR->coords();
}
