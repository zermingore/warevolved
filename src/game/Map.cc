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
    std::vector<std::shared_ptr<Cell>> vec(_nbColumns);

    // Allocates each Cell
    for (unsigned int j = 0; j < _nbColumns; j++)
      vec[j] = std::make_shared<Cell> ();

    _cells.push_back(vec);
  }

  CURSOR->setLimits(_nbColumns, _nbLines);

  // TODO read informations from a map file
  for (unsigned int i = 0; i < _nbColumns; ++i)
    for (unsigned int j = 0; j < _nbLines; ++j)
      _cells[i][j]->setTerrain(E_TERRAIN_FOREST);
}

void Map::moveUnit()
{
  Coords c = g_status->selectedCell();
  std::shared_ptr<Unit> tmp(_cells[c.x][c.y]->unit());

  tmp->setCellCoordinates(CURSOR->coords());
  _cells[CURSOR->x()][CURSOR->y()]->setUnit(tmp);
  _cells[c.x][c.y]->removeUnit();
}

void Map::moveUnit(std::shared_ptr<Unit> unit, Coords c)
{
  Coords tmp = unit->coords();
  unit->setCellCoordinates(c);
  _cells[c.x][c.y]->setUnit(unit);
  _cells[tmp.x][tmp.y]->removeUnit();
}
