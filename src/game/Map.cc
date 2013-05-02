#include <game/Map.hh>
#include <game/Cell.hh>
#include <game/Terrain.hh>


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


void Map::init(ResourcesManager *rm)
{
  // TODO read informations from a map file

  Terrain *forest = new Terrain(E_TERRAINS_FOREST, rm);

  for (unsigned int i = 0; i < _nbColumns; ++i)
	for (unsigned int j = 0; j < _nbLines; ++j)
	{
	  _cells[i * _nbLines + j].setTerrain(forest->getTextureId());
	}

  _cells[12].setUnit(E_UNITS_SOLDIERS);

  // rm->
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


e_units Map::getUnitId(unsigned int x, unsigned int y) {
  return _cells[x * _nbLines + y].getUnitId();
}

e_units Map::getUnitId(sf::Vector2f v) {
  return _cells[static_cast<unsigned int>(v.x * _nbLines + v.y)].getUnitId();
}

e_terrains Map::getTerrainId(unsigned int x, unsigned int y) {
  return _cells[x * _nbLines + y].getTerrainId();
}
