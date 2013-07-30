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


  _IDTST = 0;
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
# ifdef DEBUG_PERFS
  // _____perf
  sf::Clock timer;
  sf::Int64 t;

  t = timer.getElapsedTime().asMicroseconds();
  GETIMAGE(std::string("forest"));
  res1.push_back(timer.getElapsedTime().asMicroseconds() - t);

  t = timer.getElapsedTime().asMicroseconds();
  GETIMAGE("forest");
  res2.push_back(timer.getElapsedTime().asMicroseconds() - t);

  t = timer.getElapsedTime().asMicroseconds();
  GETIMAGE(&_IDTST, std::string("forest"));
  res3.push_back(timer.getElapsedTime().asMicroseconds() - t);

  this->printTimer();
# endif

  switch (_terrain)
  {
    default:
      GETIMAGE("forest")->drawAtCell(_coordinates);
  }

  if (_unit)
    _unit->draw();
}


void Cell::printTimer()
{
  sf::Int64 sum = 0;

  DEBUG_PRINT_VALUE(res1.size());
  DEBUG_PRINT("--------STD::STRING--------------");
  for (auto it : res1)
    sum += it;
  DEBUG_PRINT_VALUE(sum);
  DEBUG_PRINT_VALUE(sum / res1.size());

  sum = 0;
  DEBUG_PRINT("--------CHAR*--------------");
  for (auto it : res2)
    sum += it;
  DEBUG_PRINT_VALUE(sum);
  DEBUG_PRINT_VALUE(sum / res2.size());


  sum = 0;
  DEBUG_PRINT("--------ID------------");
  for (auto it : res3)
    sum += it;
  DEBUG_PRINT_VALUE(sum);
  DEBUG_PRINT_VALUE(sum / res3.size());
}
