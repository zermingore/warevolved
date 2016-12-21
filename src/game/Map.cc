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


Map::Map(const size_t nb_columns, const size_t nb_lines)
  : _nbColumns(nb_columns)
  , _nbLines(nb_lines)
{
  _graphicsProperties = std::make_shared<Map::MapGraphicsProperties> ();

  for (auto col(0u); col < _nbColumns; ++col)
  {
    std::vector<std::shared_ptr<Cell>> vec(_nbLines);

    // Allocate each Cell of the column
    for (auto line(0u); line < _nbLines; ++line) {
      vec[line] = std::make_shared<Cell> (col, line);
    }

    // _cells is a vector of columns
    _cells.push_back(vec);
  }

  /// \todo Read data from a map file to set the terrains
  // (should be called from Battle)
}



std::shared_ptr<Unit> Map::unit(const size_t column, const size_t line) const {
  return _cells[line][column]->unit();
}

std::shared_ptr<Unit> Map::unit(const Coords& c) const {
  return _cells[c.x][c.y]->unit();
}

e_terrain Map::getTerrain(const size_t column, const size_t line) const {
  return _cells[column][line]->terrain();
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
  if (unit->coords() == c)
  {
    Debug::error("move unit: src == dst");
    return;
  }

  Coords old(unit->coords());
  _cells[old.x][old.y]->removeUnit();
  unit->setCellCoordinates(c);
  _cells[c.x][c.y]->setUnit(unit);
}


void Map::endTurn()
{
  for (auto& it: _units[Status::battle()->currentPlayer()]) {
    it->setPlayed(false);
  }
}


void Map::newUnit(const e_unit type, const size_t column, const size_t line)
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

  auto player_id = Status::battle()->currentPlayer();
  new_unit->setCellCoordinates(Coords(column, line));
  new_unit->setPlayerId(player_id);
  _units[player_id].push_back(new_unit);
  _cells[column][line]->setUnit(new_unit);
}



void Map::dump()
{
  // Browsing the _cells array by line, even if the cells are stored by column
  //   is only to make it clearer to see
  //   (and easier to code, do not need to move the cursor manually)

  std::cout << std::endl;
  for (auto line(0u); line < _nbLines; ++line)
  {
    std::cout << line << " |";

    for (auto col(0u); col < _nbColumns; ++col)
    {
      // std::cout << "|  " << j << "," << i << " ";
      auto unit = _cells[col][line]->unit();
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
