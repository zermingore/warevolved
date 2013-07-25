#include <game/Map.hh>
#include <game/Cell.hh>
#include <game/Terrain.hh>
#include <common/enums/terrains.hh>
#include <resources/ResourcesManager.hh>
#include <common/globals.hh>


Map::Map() {
  // TODO generate a random Map, read one from a file, ...
}

Map::Map(unsigned int nbColumns, unsigned int nbLines) :
  _nbColumns (nbColumns),
  _nbLines (nbLines),
  _cells (NULL),
  _units (NULL)
{
  _cells = new Cell[nbColumns * nbLines];
  this->init();
}

Map::~Map() {
  delete[] _cells;
}


void Map::init()
{
  // TODO read informations from a map file
  for (unsigned int i = 0; i < _nbColumns; ++i)
  {
    for (unsigned int j = 0; j < _nbLines; ++j)
      _cells[i * _nbLines + j].setTerrain(E_TERRAINS_FOREST);
  }

  Unit* soldier = new Unit("soldiers");
  soldier->setCellCoordinates(1, 4);
  _cells[12].setUnit(soldier); // 8 + 4
}


unsigned int Map::getNbLines() {
  return _nbLines;
}

unsigned int Map::getNbColumns() {
  return _nbColumns;
}

Unit *Map::getUnit(unsigned int x, unsigned int y) {
  return _cells[x * _nbLines + y].getUnit();
}

Unit *Map::getUnit(Coords v) {
  return _cells[static_cast<unsigned int>(v.x * _nbLines + v.y)].getUnit();
}

e_terrains Map::getTerrain(unsigned int x, unsigned int y) {
  return _cells[x * _nbLines + y].getTerrain();
}


Image *Map::getTerrainImage(unsigned int x, unsigned int y)
{
  e_terrains terrain = _cells[x * _nbLines + y].getTerrain();

  switch (terrain)
  {
    case E_TERRAINS_FOREST:
      return GETIMAGE("forest");

    default:
      return NULL;
  }
}
