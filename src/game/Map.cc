#include <game/Map.hh>
#include <game/applications/Battle.hh>
#include <game/units/Soldier.hh>
#include <game/Player.hh>
#include <game/Cell.hh>
#include <game/Terrain.hh>
#include <interface/Cursor.hh>
#include <common/Status.hh>



Map::MapGraphicsProperties::MapGraphicsProperties()
{
  _cellWidth = 64;
  _cellHeight = 64;
  _gridThickness = 5;
  _gridOffsetX = 0;
  _gridOffsetY = 0;
}


Map::Map(Battle* battle, size_t nbColumns, size_t nbLines) :
  _nbColumns (nbColumns),
  _nbLines (nbLines),
  _battle (battle)
{
  _graphicsProperties = std::make_shared<Map::MapGraphicsProperties> ();
}


void Map::init()
{
  for (size_t i = 0; i < _nbLines; i++)
  {
    std::vector<std::shared_ptr<Cell>> vec(_nbColumns);

    // Allocates each Cell
    for (size_t j = 0; j < _nbColumns; j++)
      vec[j] = std::make_shared<Cell> (j, i);

    _cells.push_back(vec);
  }

  // building Cursors
  for (auto p: _battle->players())
    _cursors[p->id()] = std::make_shared<Cursor> ();

  _cursors[_battle->currentPlayer()]->setLimits(_nbColumns, _nbLines);

  // TODO read informations from a map file
  for (auto i = 0u; i < _nbColumns; ++i)
    for (auto j = 0u; j < _nbLines; ++j)
      _cells[i][j]->setTerrain(terrain::FOREST);
}

void Map::moveUnit()
{
  Coords c = Status::selectedCell();
  std::shared_ptr<Unit> tmp(_cells[c.x][c.y]->unit());

  auto cursor = _cursors[_battle->currentPlayer()];
  tmp->setCellCoordinates(cursor->coords());
  _cells[cursor->x()][cursor->y()]->setUnit(tmp);
  _cells[c.x][c.y]->removeUnit();
}

void Map::moveUnit(std::shared_ptr<Unit> unit, Coords c)
{
  Coords tmp = unit->coords();
  unit->setCellCoordinates(c);
  _cells[c.x][c.y]->setUnit(unit);
  _cells[tmp.x][tmp.y]->removeUnit();
}

std::shared_ptr<Unit> Map::unit(Coords c) const {
  return _cells[c.x][c.y]->unit();
}

std::shared_ptr<Unit> Map::unit(size_t x, size_t y) const {
  return _cells[x][y]->unit();
}

terrain Map::getTerrain(size_t x, size_t y) const {
  return _cells[x][y]->terrain();
}

// void Map::setUnit(std::shared_ptr<Unit> u) {
//   _cells[u->x()][u->y()]->setUnit(u);
// }

std::shared_ptr<Cursor> Map::cursor(size_t player){
  return _cursors[player];
}


void Map::endTurn()
{
  for (auto it: _units[_battle->currentPlayer()])
    it->setPlayed(false);
}


void Map::newUnit(enum unit unit, size_t line, size_t column)
{
  std::shared_ptr<Unit> new_unit;

  switch (unit)
  {
    case unit::SOLDIERS:
      new_unit = std::make_shared<Soldier> ();
      break;

    default:
      PRINTF("Unable to match this unit type");
      return;
  }

  auto player_id = _battle->currentPlayer();
  new_unit->setCellCoordinates(Coords(line, column));
  new_unit->setPlayerId(player_id);
  _units[player_id].push_back(new_unit);
}


void Map::setCursorCoords(Coords coords) {
  _cursors[_battle->currentPlayer()]->setCoords(coords);
}

size_t Map::currentPlayer() const {
  return _battle->currentPlayer();
}
