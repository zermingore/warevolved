#include <game/Map.hh>
#include <game/Cell.hh>


Map::Map() {
}

Map::Map(unsigned int nbColumns, unsigned int nbLines) :
  _nbColumns (nbColumns),
  _nbLines (nbLines)
{
  _cells = new Cell[nbColumns * nbLines];

  // TODO read informations from a map file
  _cells[12].setUnit(E_SOLDIERS);
}

Map::~Map() {
  delete[] _cells;
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

e_terrains Map::getTerrain(unsigned int x, unsigned int y) {
  return _cells[x * _nbLines + y].getTerrain();
}
