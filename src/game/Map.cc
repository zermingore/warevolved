/**
 * \file
 * \author Zermingore
 * \brief Map class implementation.
 */

#include <game/Map.hh>
#include <common/Status.hh>
#include <common/enums/terrains.hh>
#include <common/enums/units.hh>
#include <game/applications/Battle.hh>
#include <game/units/Soldier.hh>
#include <game/Player.hh>
#include <game/Cell.hh>


Map::MapGraphicsProperties::MapGraphicsProperties()
  : _cellWidth(64)
  , _cellHeight(64)
  , _gridThickness(5)
  , _gridOffsetX(0)
  , _gridOffsetY(0)
{
}


Map::Map(Battle* battle, const size_t nb_lines, const size_t nb_columns)
  : _battle(battle)
  , _nbColumns(nb_columns)
  , _nbLines(nb_lines)
{
  _graphicsProperties = std::make_shared<Map::MapGraphicsProperties> ();

  for (auto i(0u); i < _nbLines; ++i)
  {
    std::vector<std::shared_ptr<Cell>> vec(_nbColumns);

    // Allocate each Cell
    for (auto j(0u); j < _nbColumns; ++j) {
      vec[j] = std::make_shared<Cell> (i, j);
    }
    _cells.push_back(vec);
  }

  /// \todo Read data from a map file to set the terrains
  // (should be called from Battle)
}


std::shared_ptr<Unit> Map::unit(const size_t line, const size_t column) const {
  return _cells[line][column]->unit();
}

std::shared_ptr<Unit> Map::unit(const Coords& c) const {
  return _cells[c.x][c.y]->unit();
}

e_terrain Map::getTerrain(const size_t line, const size_t column) const {
  return _cells[line][column]->terrain();
}


std::shared_ptr<Unit> Map::selectUnit(const Coords c)
{
  _selectedUnit = nullptr;

  auto unit(_cells[c.x][c.y]->unit());
  if (!unit)
  {
    Debug::error("No unit to select at given coords", c.x, c.y);
    return nullptr;
  }

  _selectedUnit = unit;
  return _selectedUnit;
}


void Map::moveUnit(std::shared_ptr<Unit> unit, const Coords c)
{
  Debug::printf("before moving unit", unit->coords().x, unit->coords().y,
                "to", c.x, c.y);
  dump();

  if (unit->coords() == c)
  {
    Debug::printf("move unit: src == dst");
    return;
  }

  Coords old(unit->coords());
  _cells[old.x][old.y]->removeUnit();
  unit->setCellCoordinates(c);
  _cells[c.x][c.y]->setUnit(unit);

  Debug::printf("moved unit:", unit);
  dump();
}


void Map::endTurn()
{
  for (auto& it: _units[_battle->currentPlayer()]) {
    it->setPlayed(false);
  }
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
      assert(!"Unable to match this unit type");
      return;
  }

  auto player_id = _battle->currentPlayer();
  new_unit->setCellCoordinates(Coords(line, column));
  new_unit->setPlayerId(player_id);
  _units[player_id].push_back(new_unit);
  _cells[line][column]->setUnit(new_unit);
}



void Map::dump()
{
  std::cout << "Units: 0,2 4,1 3,4 3,6\n";
  std::cout << std::endl;
  for (auto i(0u); i < _nbLines; ++i)
  {
    std::cout << i << " |";
    for (auto j(0u); j < _nbColumns; ++j)
    {
      // std::cout << "|  " << j << "," << i << " ";
      auto unit = _cells[i][j]->unit();
      if (unit) {
        unit == _selectedUnit ? std::cout << "#" : std::cout << "X";
      }
      else {
        std::cout << ".";
      }
    }

    std::cout << "|" << std::endl;
  }
}
