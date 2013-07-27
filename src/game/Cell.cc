#include <game/Cell.hh>
#include <common/include.hh>
#include <common/enums/units.hh>


Cell::Cell() :
  _terrain (E_TERRAINS_NONE),
  _unit (nullptr),
  _terrainTextureId (0),
  _unitTextureId (0)
{
}

Cell::~Cell() {
}

Unit *Cell::getUnit() {
  return _unit;
}

e_terrains Cell::getTerrain() {
  return _terrain;
}


unsigned int Cell::getUnitTextureId() {
  return _unitTextureId;
}

unsigned int Cell::getTerrainTextureId() {
  return _terrainTextureId;
}

void Cell::setUnit(Unit *unit) {
  _unit = unit;
}

void Cell::setTerrain(e_terrains terrain) {
  _terrain = terrain;
}
