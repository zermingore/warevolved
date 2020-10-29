/**
 * \file
 * \date April 19, 2013
 * \author Zermingore
 * \brief Map class implementation
 */

#include <game/Map.hh>

#include <lib/pugixml.hh>

#include <debug/Debug.hh>
#include <config/Settings.hh>
#include <game/Battle.hh>
#include <game/Cell.hh>
#include <game/Player.hh>
#include <game/Status.hh>
#include <game/Terrain.hh>
#include <game/TerrainsHandler.hh>
#include <game/units/UnitsFactory.hh>
#include <game/units/Vehicle.hh>
#include <game/Building.hh>
#include <interface/Cursor.hh>



Map::Map(size_t nb_columns, size_t nb_lines)
  : _nbColumns(nb_columns)
  , _nbLines(nb_lines)
{
  for (auto col(0u); col < _nbColumns; ++col)
  {
    std::vector<std::shared_ptr<Cell>> vec(_nbLines);

    // Allocate each Cell of the column
    for (auto line(0u); line < _nbLines; ++line)
    {
      vec[line] = std::make_shared<Cell> (col, line, e_terrain::PLAIN);
    }

    // _cells is a vector of columns
    _cells.emplace_back(vec);
  }
}



void Map::addBuilding(const std::vector<std::shared_ptr<Coords>> &coords)
{
  _buildings.push_back(std::make_shared<Building>(coords));
}



std::shared_ptr<Unit> Map::unit(size_t column, size_t line) const
{
  assert(column < _nbColumns && line < _nbLines);
  return _cells[column][line]->unit();
}



std::shared_ptr<Unit> Map::unit(const Coords& c) const
{
  return _cells[c.c][c.l]->unit();
}



void Map::setTerrain(size_t column, size_t line, e_terrain terrain)
{
  _cells[column][line]->setTerrain(terrain);
}



void Map::clearHighlights()
{
  for (auto col(0u); col < _nbColumns; ++col)
  {
    for (auto line(0u); line < _nbLines; ++line)
    {
      _cells[col][line]->setHighlight(false);
    }
  }
}


void Map::selectUnit(const Coords& c)
{
  // Retrieve the unit
  auto unit(_cells[c.c][c.l]->unit());
  if (!unit)
  {
    ERROR("No unit to select at given coords", c.c, c.l);
  }

  _lockSelectedUnitUpdate.lock();
  _selectedUnit = unit;
  _lockSelectedUnitUpdate.unlock();
}


std::shared_ptr<Unit> Map::selectedUnit()
{
  if (!_selectedUnit)
  {
    PRINTF("No selecting unit -> auto update");
    game::Status::player()->updateSelectedUnit();
  }

  return _selectedUnit;
}


void Map::moveUnit(const Coords& c)
{
  _lockSelectedUnitUpdate.lock();

  Coords old(_selectedUnit->coords());
  assert(_cells[old.c][old.l]->unit()->played() == false);
  _cells[old.c][old.l]->unit()->stashCoords();

  _cells[old.c][old.l]->unit()->setMoved(true);
  _cells[old.c][old.l]->removeUnit();
  _selectedUnit->setCoords(c);
  _cells[c.c][c.l]->setUnit(_selectedUnit);

  _lockSelectedUnitUpdate.unlock();
}



void Map::endTurn()
{
  for (auto& it: _units[game::Status::battle()->currentPlayer()])
  {
    it->setPlayed(false);
    it->setMoved(false);
  }
}



void Map::newUnit(const std::shared_ptr<Unit>& unit, size_t column, size_t line)
{
  boundaryChecks(column, line);

  unit->setCoords({ column, line });
  _units[unit->playerId()].emplace_back(unit);
  _cells[column][line]->setUnit(unit);
}



void Map::newUnit(e_unit type,
                  size_t column,
                  size_t line,
                  size_t player_id,
                  int hp,
                  bool played)
{
  boundaryChecks(column, line);

  // Explicitly using a shared_ptr
  std::shared_ptr<Unit> new_unit(UnitsFactory::createUnit(type));
  new_unit->setCoords({ column, line });
  new_unit->setPlayerId(player_id);
  new_unit->setHp(hp);
  new_unit->setPlayed(played);
  _units[player_id].emplace_back(new_unit);
  _cells[column][line]->setUnit(new_unit);
}



e_attack_result Map::attackResult(bool attacker_status,
                                  bool defender_status) const
{
  /// \todo handle other status (unit down)
  if (attacker_status && defender_status)
  {
    return e_attack_result::BOTH_DIED;
  }

  if (attacker_status)
  {
    return e_attack_result::ATTACKER_DIED;
  }

  if (defender_status)
  {
    return e_attack_result::DEFENDER_DIED;
  }

  return e_attack_result::NONE_DIED;
}



std::pair<size_t, size_t> Map::damageValues(const Unit& attacker,
                                            const Unit& defender)
{
  // Compute attacker damages
  auto def_cell = _cells[defender.c()][defender.l()];
  const auto def_terrain = TerrainsHandler::get(def_cell->terrain());

  int dmg_attack =
    static_cast<int> (attacker.attackValue()) - def_terrain.cover();
  auto attacker_damages = std::max(1, dmg_attack);

  // No strike-back damages if the defender dies
  if (defender.hp() - attacker_damages <= 0)
  {
    return { attacker_damages, 0 };
  }

  // Compute defender strike-back damages
  auto att_cell = _cells[attacker.c()][attacker.l()];
  auto att_terrain = TerrainsHandler::get(att_cell->terrain());

  int dmg_def =
    static_cast<int> (defender.attackValue() / 2) - att_terrain.cover();
  auto defender_damages = std::max(1, dmg_def);


  return { attacker_damages, defender_damages };
}



e_attack_result Map::attack(const std::shared_ptr<Unit>& defender)
{
  _lockSelectedUnitUpdate.lock();
  assert(_selectedUnit && defender);

  auto damages = damageValues(*_selectedUnit, *defender);

  bool defender_died = false;
  defender->setHp(defender->hp() - static_cast<int> (damages.first));
  if (defender->hp() <= 0)
  {
    _cells[defender->c()][defender->l()]->removeUnit();
    defender_died = true;
  }

  // getting attacker status after strike back
  _selectedUnit->setHp(_selectedUnit->hp() - static_cast<int> (damages.second));
  bool attacker_died = false;
  if (_selectedUnit->hp() <= 0)
  {
    NOTICE("attacker died");
    _cells[_selectedUnit->c()][_selectedUnit->l()]->removeUnit();
    attacker_died = true;
  }

  _lockSelectedUnitUpdate.unlock();

  return attackResult(attacker_died, defender_died);
}



e_attack_result Map::attack(const std::shared_ptr<Cell>& target_cell)
{
  auto defender = target_cell->unit();
  if (!defender)
  {
    ERROR("Attacking empty cell");
    return e_attack_result::NONE_DIED;
  }

  return attack(defender);
}



std::optional<std::shared_ptr<Building>> Map::getBuilding(const Coords coord)
{
  for (auto b: _buildings)
  {
    for (const auto c: b->getCoords())
    {
      if (c->c == coord.c && c->l == coord.l)
      {
        return b;
      }
    }
  }

  return std::nullopt;
}



e_attack_result Map::attackBuilding(const Coords attackerCoords)
{
  auto building = getBuilding(attackerCoords);
  assert(building);

  if ((*building)->getUnits().size() == 0)
  {
    _selectedUnit->setPlayed(true);
    (*building)->addUnit(_selectedUnit);
    _cells[_selectedUnit->c()][_selectedUnit->l()]->removeUnit();
    return e_attack_result::NONE_DIED;
  }

  const auto def_attacker = 3;
  const auto def_defender = 5;

  auto dmg_att{static_cast<int> (_selectedUnit->attackValue()) - def_defender};
  auto attacker_damages = std::max(1, dmg_att);

  _lockSelectedUnitUpdate.lock();

  while ((*building)->getUnits().size() > 0)
  {
    for (auto defender: (*building)->getUnits())
    {
      // The attacker receives damages first
      auto dmg_def{static_cast<int> (defender->attackValue()) - def_attacker};
      auto defender_damages = std::max(1, dmg_def);

      _selectedUnit->setHp(_selectedUnit->hp() - defender_damages);
      if (_selectedUnit->hp() <= 0)
      {
        _cells[_selectedUnit->c()][_selectedUnit->l()]->removeUnit();
        _lockSelectedUnitUpdate.unlock();
        return e_attack_result::ATTACKER_DIED;
      }
    }

    auto defender{(*building)->getUnits()[0]};
    defender->setHp(defender->hp() - attacker_damages);
    if (defender->hp() <= 0)
    {
      auto units{(*building)->getUnits()};
      units.erase(units.begin());
    }
  }

  _lockSelectedUnitUpdate.unlock();
  return e_attack_result::DEFENDER_DIED;
}



std::unique_ptr<pugi::xml_document> Map::dump()
{
  std::unique_ptr<pugi::xml_document> doc{new pugi::xml_document};

  // 'version' node
  auto version{doc->append_child("game_version")};
  version.append_attribute("major") = Settings::version()[0];
  version.append_attribute("minor") = Settings::version()[1];
  version.append_attribute("patch") = Settings::version()[2];

  // Main 'map' node
  auto map{doc->append_child("map")};

  // 'metadata' node
  auto metadata{map.append_child("metadata")};

  // Map size
  auto map_size{metadata.append_child("map_size")};
  map_size.append_attribute("nb_columns") = _nbColumns;
  map_size.append_attribute("nb_lines") = _nbLines;

  // Players
  auto players{metadata.append_child("players")};

  // Current Player
  players.append_child("current_player")
    .append_child(pugi::node_pcdata)
    .set_value(std::to_string(game::Status::battle()->currentPlayer())
    .c_str());

  for (const auto& player: game::Status::battle()->players())
  {
    auto n_player{players.append_child("player")};

    auto n_color{n_player.append_child("color")};
    n_color.append_attribute("r") = static_cast<int> (player->color().r);
    n_color.append_attribute("g") = static_cast<int> (player->color().g);
    n_color.append_attribute("b") = static_cast<int> (player->color().b);

    auto n_cursor{n_player.append_child("cursor")};
    n_cursor.append_attribute("col")  = player->cursor()->coords().c;
    n_cursor.append_attribute("line") = player->cursor()->coords().l;
  }


  // 'cells' node
  auto cells = map.append_child("cells");
  for (auto col{0u}; col < _nbColumns; ++col)
  {
    for (auto line{0u}; line < _nbLines; ++line)
    {
      auto cell{cells.append_child("cell")};

      // Coordinates
      auto coords{cell.append_child("coordinates")};
      coords.append_attribute("col") = col;
      coords.append_attribute("line") = line;

      // Terrain
      const auto i_terrain{ static_cast<int> (_cells[col][line]->terrain()) };
      cell.append_child("terrain")
        .append_child(pugi::node_pcdata)
        .set_value(std::to_string(i_terrain).c_str());

      // Unit
      if (const auto u{_cells[col][line]->unit()})
      {
        auto unit{cell.append_child("unit")};
        unit.append_attribute("type") = static_cast<int> (u->type());
        unit.append_attribute("player_id") = u->playerId();
        unit.append_attribute("hp") = u->hp();
        unit.append_attribute("played") = u->played();

        // Crew
        if (u->crewSize() <= 0)
        {
          continue; // no crew -> skip to the next unit
        }

        auto crew{unit.append_child("crew")};
        auto vehicle{std::static_pointer_cast<Vehicle> (u)};
        for (const auto& mbr: vehicle->crew())
        {
          auto n{crew.append_child("member")};
          n.append_attribute("role") = static_cast<int> (mbr.first);

          n.append_attribute("type") = static_cast<int> (mbr.second->type());
          n.append_attribute("player_id") = mbr.second->playerId();
          n.append_attribute("hp") = mbr.second->hp();
          n.append_attribute("played") = mbr.second->played();
        }
      }
    }
  }

  return doc;
}



void Map::stashUnit(const Unit& unit)
{
  _cells[unit.c()][unit.l()]->removeUnit();
}



void Map::stashPopUnit(const Unit& unit)
{
  newUnit(unit.type(), unit.c(), unit.l(), unit.playerId(), unit.hp(), true);
}



constexpr void Map::boundaryChecks(size_t column, size_t line)
{
  if (column >= _nbColumns || line >= _nbLines)
  {
    /// \todo use string format.
    /// \warning __PRETTY_FUNCTION__ g++/clang++ only
    // std::stringstream sstr;
    // sstr << "In " << __PRETTY_FUNCTION__ << '\n';
    // sstr << "Invalid coordinates: (" << column << ", " << line << ") "
    //      << "Exceed: (" << _nbColumns - 1 << ", " << _nbLines - 1 << ")";
    throw std::out_of_range("Invalid provided coordinates");
  }
}



Map::MapIterator& Map::MapIterator::operator++()
{
  _colIdx = (_colIdx + 1) % _nbColumns;
  if (_colIdx == 0)
  {
    ++_lineIdx; // no boundary check: end() == last_col; out of bound line
  }

  return *this;
}

Cell Map::MapIterator::operator++(int)
{
  Cell ret(*_cells[_colIdx][_lineIdx]);
  ++*this;
  return ret;
}
