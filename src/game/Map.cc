#include <game/Map.hh>
#include <game/Cell.hh>
#include <game/Terrain.hh>
#include <common/enums/terrains.hh>
#include <resources/ResourcesManager.hh>
#include <common/globals.hh>


Map::Map(unsigned int nbColumns, unsigned int nbLines) :
  _nbColumns (nbColumns),
  _nbLines (nbLines)
{
}

void Map::init()
{
  for (unsigned int i = 0; i < _nbLines; i++)
  {
    std::vector<Cell> vec(_nbColumns);
    _cells.push_back(vec);
  }

  CURSOR->setLimits(_nbColumns, _nbLines);

  // TODO read informations from a map file
  for (unsigned int i = 0; i < _nbColumns; ++i)
    for (unsigned int j = 0; j < _nbLines; ++j)
      _cells[i][j].setTerrain(E_TERRAIN_FOREST);
}

Unit *Map::getUnit(unsigned int x, unsigned int y) {
  return _cells[x][y].getUnit();
}

Unit *Map::getUnit(Coords v) {
  return _cells[v.x][v.y].getUnit();
}

void Map::setUnit(Unit &u) {
  _cells[u.getCellX()][u.getCellY()].setUnit(u);
}

e_terrain Map::getTerrain(unsigned int x, unsigned int y) {
  return _cells[x][y].getTerrain();
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

void Map::moveUnit()
{
  Coords c = g_status->getSelectedCell();

  Unit *tmp = _cells[c.x][c.y].getUnit();
  tmp->setCellCoordinates(CURSOR->getX(), CURSOR->getY());
  _cells[CURSOR->getX()][CURSOR->getY()].setUnit(*tmp);
  _cells[c.x][c.y].removeUnit();
}
