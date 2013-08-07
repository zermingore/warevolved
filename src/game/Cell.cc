#include <game/Cell.hh>
#include <common/macros.hh>
#include <common/globals.hh>
#include <common/enums/units.hh>


Cell::Cell() :
  _terrain (E_TERRAINS_NONE),
  _unit (nullptr)
{
  static unsigned int x = 0;
  static unsigned int y = 0;

  _coordinates.x = x++ / NB_COLUMNS;
  _coordinates.y = y++ % NB_LINES;
}

Cell::~Cell() {
}

Unit *Cell::getUnit() {
  return _unit;
}

e_terrains Cell::getTerrain() {
  return _terrain;
}

void Cell::setUnit(Unit &unit) {
  _unit = &unit;
}

void Cell::removeUnit() {
  _unit = nullptr;
}

void Cell::setTerrain(const e_terrains terrain) {
  _terrain = terrain;
}


void Cell::draw()
{
  // TODO check if we print the cell (scroll case)

  switch (_terrain)
  {
    default:
      GETIMAGE("forest")->drawAtCell(_coordinates);
  }

  if (_unit)
    _unit->draw();
}
