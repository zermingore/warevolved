# include <common/State.hh>
# include <common/macros.hh>
# include <common/globals.hh>


State::State(e_mode mode) :
  _mode (mode)
{
  if (g_status->getCursor())
    _cursorCoords = CURSOR->getCoords();
}


e_mode State::getMode()
{
  return _mode;
}

Coords State::getCursorCoords()
{
  return _cursorCoords;
}
