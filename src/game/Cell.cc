#include <game/Cell.hh>
#include <common/terrains.hh>
#include <common/units.hh>
#include <common/include.hh>

Cell::Cell() :
  _terrain (E_TERRAINS_FOREST), // we put a default terrain
  _unit (E_UNITS_NONE)
{
}

Cell::~Cell() {
}

// _________________________ GETTERS _________________________ //
e_units Cell::getUnit() {
  return _unit;
}

e_terrains Cell::getTerrain() {
  return _terrain;
}

// _________________________ SETTERS _________________________ //
void Cell::setUnit(e_units unit) {
  _unit = unit;
}

void Cell::setTerrain(e_terrains terrain) {
  _terrain = terrain;
}
