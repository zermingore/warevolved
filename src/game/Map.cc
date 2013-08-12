#include <game/Map.hh>
#include <game/Cell.hh>
#include <game/Terrain.hh>
#include <common/enums/terrains.hh>
#include <resources/ResourcesManager.hh>
#include <common/globals.hh>


Map::Map(unsigned int nbColumns, unsigned int nbLines) :
  _nbColumns (nbColumns),
  _nbLines (nbLines),
  _cells (nullptr)
{
}

Map::~Map() {
  delete[] _cells;
}


void Map::init()
{
  _cells = new Cell*[_nbColumns * _nbLines];
  CURSOR->setLimits(_nbColumns, _nbLines);

  // TODO read informations from a map file
  for (unsigned int i = 0; i < _nbColumns; ++i)
    for (unsigned int j = 0; j < _nbLines; ++j)
    {
      _cells[i * _nbColumns + j] = new Cell;
      _cells[i * _nbLines + j]->setTerrain(E_TERRAIN_FOREST);
    }
}


unsigned int Map::getNbLines() {
  return _nbLines;
}

unsigned int Map::getNbColumns() {
  return _nbColumns;
}

Unit *Map::getUnit(unsigned int x, unsigned int y) {
  return _cells[x * _nbLines + y]->getUnit();
}

Unit *Map::getUnit(Coords v) {
  return _cells[static_cast<unsigned int>(v.x * _nbLines + v.y)]->getUnit();
}

void Map::setUnit(Unit &u) {
  _cells[static_cast<unsigned int>(u.getCellX() * _nbLines + u.getCellY())]->setUnit(u);
}

e_terrain Map::getTerrain(unsigned int x, unsigned int y) {
  return _cells[x * _nbLines + y]->getTerrain();
}


//Image *Map::getTerrainImage(unsigned int x, unsigned int y)
//{
//  e_terrains terrain = _cells[x * _nbLines + y]->getTerrain();
//
//  switch (terrain)
//  {
//    case E_TERRAINS_FOREST:
//      return GETIMAGE("forest");
//
//    default:
//      return nullptr;
//  }
//}

Cell **Map::getCells() {
  return _cells;
}


void Map::moveUnit()
{
  Coords c = g_status->getSelectedCell();

  Unit *tmp = _cells[c.x * _nbColumns + c.y]->getUnit();
  tmp->setCellCoordinates(CURSOR->getX(), CURSOR->getY());
  _cells[CURSOR->getX() * _nbColumns + CURSOR->getY()]->setUnit(*tmp);
  _cells[c.x * _nbColumns + c.y]->removeUnit();
}
