#include <game/Cell.hh>
#include <common/macros.hh>
#include <common/globals.hh>
#include <common/enums/units.hh>


Cell::Cell() :
  _terrain (E_TERRAINS_NONE),
  _unit (nullptr),
  _terrainTextureId (0),
  _unitTextureId (0)
{
  static unsigned int x = 0;
  static unsigned int y = 0;

  _coordinates.x = x++ / NB_COLUMNS - NB_COLUMNS; //why - NB_COLUMNS required
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


unsigned int Cell::getUnitTextureId() {
  return _unitTextureId;
}

unsigned int Cell::getTerrainTextureId() {
  return _terrainTextureId;
}

void Cell::setUnit(Unit &unit) {
  _unit = &unit;
}

void Cell::setTerrain(const e_terrains terrain) {
  _terrain = terrain;
}


void Cell::draw()
{
  switch (_terrain)
  {
    default:
      GETIMAGE("forest")->drawAtCell(_coordinates);
  }

  if (_unit)
    _unit->draw();
}
