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
  g_status->setNbColumns(nbColumns);
  g_status->setNbLines(nbLines);
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
  Coords c = g_status->selectedCell();

  std::shared_ptr<Unit> tmp(_cells[c.x][c.y].unit());
  tmp->setCellCoordinates(CURSOR->x(), CURSOR->y());
  _cells[CURSOR->x()][CURSOR->y()].setUnit(tmp);
  _cells[c.x][c.y].removeUnit();
}
