/**
 * \file
 * \author Zermingore
 * \brief Map class implementation.
 */

#include <game/Map.hh>
#include <game/applications/Battle.hh>
#include <game/units/Soldier.hh>
#include <game/Player.hh>
#include <game/Cell.hh>
#include <game/Terrain.hh>
#include <interface/Cursor.hh>
#include <common/Status.hh>
#include <common/enums/units.hh>


Map::MapGraphicsProperties::MapGraphicsProperties()
  : _cellWidth(64)
  , _cellHeight(64)
  , _gridThickness(5)
  , _gridOffsetX(0)
  , _gridOffsetY(0)
{
}


Map::Map(Battle* battle, const size_t nb_columns, const size_t nb_lines)
  : _battle (battle)
  , _nbColumns (nb_columns)
  , _nbLines (nb_lines)
{
  _graphicsProperties = std::make_shared<Map::MapGraphicsProperties> ();

  for (auto i(0u); i < _nbLines; i++)
  {
    std::vector<std::shared_ptr<Cell>> vec(_nbColumns);

    // Allocate each Cell
    for (auto j(0u); j < _nbColumns; j++)
      vec[j] = std::make_shared<Cell> (j, i);

    _cells.push_back(vec);
  }

  /// \todo Read informations from a map file
  for (auto i(0u); i < _nbColumns; ++i)
  {
    for (auto j(0u); j < _nbLines; ++j)
      _cells[i][j]->setTerrain(e_terrain::FOREST);
  }
}

std::shared_ptr<Unit> Map::unit(const size_t x, const size_t y) const {
  return _cells[x][y]->unit();
}

std::shared_ptr<Unit> Map::unit(const Coords& c) const {
  return _cells[c.x][c.y]->unit();
}

e_terrain Map::getTerrain(const size_t x, const size_t y) const {
  return _cells[x][y]->terrain();
}

size_t Map::currentPlayer() const {
  return _battle->currentPlayer();
}


void Map::moveUnit()
{
  const Coords c(Status::selectedCell());
  std::shared_ptr<Unit> tmp(_cells[c.x][c.y]->unit());
  const auto cursor(_battle->getCurrentPlayer()->interface()->cursor());

  tmp->setCellCoordinates(cursor->coords());
  _cells[cursor->x()][cursor->y()]->setUnit(tmp);
  _cells[c.x][c.y]->removeUnit();
}

void Map::moveUnit(std::shared_ptr<Unit> unit, Coords c)
{
  Coords tmp(unit->coords());
  unit->setCellCoordinates(c);
  _cells[c.x][c.y]->setUnit(unit);
  _cells[tmp.x][tmp.y]->removeUnit();
}


void Map::endTurn()
{
  for (auto& it: _units[_battle->currentPlayer()])
    it->setPlayed(false);
}


void Map::newUnit(const e_unit type, const size_t line, const size_t column)
{
  std::shared_ptr<Unit> new_unit;

  switch (type)
  {
    case e_unit::SOLDIERS:
      new_unit = std::make_shared<Soldier> ();
      break;

    default:
      assert(false && "Unable to match this unit type");
      return;
  }

  auto player_id = _battle->currentPlayer();
  new_unit->setCellCoordinates(Coords(line, column));
  new_unit->setPlayerId(player_id);
  _units[player_id].push_back(new_unit);

  _cells[line][column]->setUnit(new_unit);
}
