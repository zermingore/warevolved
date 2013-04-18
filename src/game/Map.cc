#include <game/Map.hh>

Map::Map()
{
}

Map::Map(unsigned int nbColumns, unsigned int nbLines) :
  _nbColumns (nbColumns),
  _nbLines (nbLines)
{
}


Map::~Map()
{
}


unsigned int Map::getNbLines()
{
  return _nbLines;
}

unsigned int Map::getNbColumns()
{
  return _nbColumns;
}
