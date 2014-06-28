#include <game/Cell.hh>
#include <common/macros.hh>
#include <common/globals.hh>
#include <common/enums/units.hh>


Cell::Cell() :
  _terrain (E_TERRAIN_NONE),
  _unit (nullptr),
  _highlight (false),
  _highlightColor (255, 255, 255)
{
  static unsigned int x = 0;
  static unsigned int y = 0;

  _coords.x = x++ / NB_COLUMNS;
  _coords.y = y++ % NB_LINES;
}

void Cell::draw()
{
  // TODO check if we print the cell (scroll case)

  switch (_terrain)
  {
    default:
      GETIMAGE("forest").drawAtCell(_coords);
  }

  if (_highlight)
  {
    Image &highlight = GETIMAGE("highlight");
    highlight.sprite()->setColor(_highlightColor);
    highlight.drawAtCell(_coords);
  }

  if (_unit)
    _unit->draw();
}
