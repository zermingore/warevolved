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

  _coordinates.x = x++ / NB_COLUMNS;
  _coordinates.y = y++ % NB_LINES;
}

Unit *Cell::getUnit() {
  return _unit;
}

e_terrain Cell::getTerrain() {
  return _terrain;
}

void Cell::setUnit(Unit &unit) {
  _unit = &unit;
}

void Cell::removeUnit() {
  _unit = nullptr;
}

void Cell::setTerrain(const e_terrain terrain) {
  _terrain = terrain;
}

void Cell::setHighlight(bool highlight) {
  _highlight = highlight;
}

void Cell::setHighlightColor(Color color) {
  _highlightColor = color;
}

void Cell::draw()
{
  // TODO check if we print the cell (scroll case)

  switch (_terrain)
  {
    default:
      GETIMAGE("forest")->drawAtCell(_coordinates);
  }

  if (_highlight)
  {
    Image *highlight = GETIMAGE("highlight");
    highlight->getSprite()->setColor(_highlightColor);
    highlight->drawAtCell(_coordinates);
  }

  if (_unit)
    _unit->draw();
}
