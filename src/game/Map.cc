/**
 * \file
 * \date April 19, 2013
 * \author Zermingore
 * \brief Map class implementation.
 */

#include <game/Map.hh>

#include <debug/Debug.hh>
#include <common/Status.hh>
#include <common/enums/terrains.hh>
#include <common/enums/units.hh>
#include <game/Battle.hh>
#include <game/units/UnitFactory.hh>
#include <game/Player.hh>
#include <game/Cell.hh>



Map::Map(const size_t nb_columns, const size_t nb_lines)
  : _nbColumns(nb_columns)
  , _nbLines(nb_lines)
{
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
  return _cells[c.c][c.l]->unit();
}

e_terrain Map::getTerrain(const size_t column, const size_t line) const {
  return _cells[column][line]->terrain();
}


void Map::selectUnit(const Coords c)
{
  // allow to select another unit if already one is selected ?
  _selectedUnit = nullptr;

  auto unit(_cells[c.c][c.l]->unit());
  if (!unit) {
    ERROR("No unit to select at given coords", c.c, c.l);
  }

  _selectedUnit = unit;
}


void Map::moveUnit(const Coords c)
{
  if (_selectedUnit->coords() == c)
  {
    ERROR("Moving unit at coordinates:", c.c, c.l);
    assert("!move unit: src == dst");
  }

  Coords old(_selectedUnit->coords());
  assert(_cells[old.c][old.l]->unit()->played() == false);

  _cells[old.c][old.l]->unit()->setPlayed(true);
  _cells[old.c][old.l]->removeUnit();
  _selectedUnit->setCellCoordinates(c);
  _cells[c.c][c.l]->setUnit(_selectedUnit);
}


void Map::endTurn()
{
  for (auto& it: _units[Status::battle()->currentPlayer()]) {
    it->setPlayed(false);
  }
}


void Map::newUnit(const e_unit type,
                  const size_t column,
                  const size_t line,
                  int player_id)
{
  auto new_unit(UnitFactory::createUnit(type));

  // assign the unit to the given player or to the current one
  if (player_id == -1) {
    player_id = static_cast<int> (Status::battle()->currentPlayer());
  }

  new_unit->setCellCoordinates(Coords(column, line));
  new_unit->setPlayerId(player_id);
  _units[player_id].push_back(new_unit);
  _cells[column][line]->setUnit(new_unit);
}


e_attack_result Map::attackResult(bool attacker_status, bool defender_status)
{
  /// \todo handle other status (unit down)
  if (attacker_status == true && defender_status == true) {
    return e_attack_result::BOTH_DIED;
  }

  if (attacker_status == true) {
    return e_attack_result::ATTACKER_DIED;
  }

  if (defender_status == true) {
    return e_attack_result::DEFENDER_DIED;
  }

  return e_attack_result::NONE_DIED;
}


e_attack_result Map::attack(std::shared_ptr<Unit> defender)
{
  assert(_selectedUnit && defender);

  // getting defender status
  defender->setHP(defender->hp() - static_cast<int> (_selectedUnit->attackValue()));
  bool defender_died = false;
  if (defender->hp() <= 0)
  {
    _cells[defender->c()][defender->l()]->removeUnit();
    defender_died = true;
  }

  // getting attacker status after strike back
  _selectedUnit->setHP(_selectedUnit->hp() - static_cast<int> (defender->attackValue()) / 2);
  bool attacker_died = false;
  if (_selectedUnit->hp() <= 0)
  {
    NOTICE("attacker died");
    _cells[_selectedUnit->c()][_selectedUnit->l()]->removeUnit();
    attacker_died = true;
  }

  return attackResult(attacker_died, defender_died);
}


e_attack_result Map::attack(std::shared_ptr<Cell> target_cell)
{
  assert(_selectedUnit && target_cell);

  auto defender = target_cell->unit();
  if (!defender)
  {
    NOTICE("Attacking empty cell");
    return e_attack_result::NONE_DIED;
  }

  return attack(defender);
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
