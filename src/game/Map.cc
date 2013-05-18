#include <game/Map.hh>
#include <game/Cell.hh>
#include <game/Terrain.hh>
#include <common/terrains.hh>
#include <resources/ResourcesManager.hh>
#include <common/globals.hh>


Map::Map() {
  // TODO generate a random Map, read one from a file, ...
}

Map::Map(unsigned int nbColumns, unsigned int nbLines) :
  _nbColumns (nbColumns),
  _nbLines (nbLines)
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

  _cells[12].setUnit(E_UNITS_SOLDIERS);
}


unsigned int Map::getNbLines() {
  return _nbLines;
}

unsigned int Map::getNbColumns() {
  return _nbColumns;
}

e_units Map::getUnit(unsigned int x, unsigned int y) {
  return _cells[x * _nbLines + y].getUnit();
}

e_units Map::getUnit(sf::Vector2f v) {
  return _cells[static_cast<unsigned int>(v.x * _nbLines + v.y)].getUnit();
}

e_terrains Map::getTerrain(unsigned int x, unsigned int y) {
  return _cells[x * _nbLines + y].getTerrain();
}


Image* Map::getTerrainImage(unsigned int x, unsigned int y) {
  e_terrains terrain = _cells[x * _nbLines + y].getTerrain();

  switch (terrain)
  {
	case E_TERRAINS_FOREST:
	  return GETIMAGE("forest");
	default:
	  return NULL;
  }
}



// e_units Map::getUnitId(unsigned int x, unsigned int y) {
//   return _cells[x * _nbLines + y].getUnitId();
// }

// e_units Map::getUnitId(sf::Vector2f v) {
//   return _cells[static_cast<unsigned int>(v.x * _nbLines + v.y)].getUnitId();
// }

// e_terrains Map::getTerrainId(unsigned int x, unsigned int y) {
//   return _cells[x * _nbLines + y].getTerrainId();
// }
