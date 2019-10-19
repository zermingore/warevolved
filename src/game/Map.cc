/**
 * \file
 * \date April 19, 2013
 * \author Zermingore
 * \brief Map class implementation.
 */

#include <game/Map.hh>

#include <debug/Debug.hh>

#include <common/enums/terrains.hh>
#include <common/enums/units.hh>
#include <game/Status.hh>
#include <game/Battle.hh>
#include <game/units/UnitsFactory.hh>
#include <game/units/Vehicle.hh>
#include <game/Player.hh>
#include <game/Cell.hh>
#include <game/Terrain.hh>
#include <game/TerrainsHandler.hh>
#include <interface/Cursor.hh>



Map::Map(size_t nb_columns, size_t nb_lines)
  : _nbColumns(nb_columns)
  , _nbLines(nb_lines)
{
  for (auto col(0u); col < _nbColumns; ++col)
  {
    std::vector<std::shared_ptr<Cell>> vec(_nbLines);

    // Allocate each Cell of the column
    for (auto line(0u); line < _nbLines; ++line) {
      vec[line] = std::make_shared<Cell> (col, line, e_terrain::PLAIN);
    }

    // _cells is a vector of columns
    _cells.push_back(vec);
  }
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



e_terrain Map::getTerrain(size_t column, size_t line) const
{
  return _cells[column][line]->terrain();
}



void Map::setTerrain(size_t column, size_t line, e_terrain terrain)
{
  _cells[column][line]->setTerrain(terrain);
}



void Map::selectUnit(const Coords& c)
{
  // Retrieve the unit
  auto unit(_cells[c.c][c.l]->unit());
  if (!unit) {
    ERROR("No unit to select at given coords", c.c, c.l);
  }

  _lockSelectedUnitUpdate.lock();
  _selectedUnit = unit;
  _lockSelectedUnitUpdate.unlock();
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



void Map::newUnit(std::shared_ptr<Unit> unit, size_t column, size_t line)
{
  // Sanity check: valid coordinates
  if (column >= _nbColumns || line >= _nbLines)
  {
    std::stringstream sstr;
    sstr << "In " << __PRETTY_FUNCTION__ << '\n'; /// \warning g++/clang++ only
    sstr << "Invalid provided coordinates: (" << column << ", " << line << ") "
         << "Exceed: (" << _nbColumns - 1 << ", " << _nbLines - 1 << ")";

    throw std::out_of_range(sstr.str());
  }

  unit->setCoords({ column, line });
  _units[unit->playerId()].push_back(unit);
  _cells[column][line]->setUnit(unit);
}



void Map::newUnit(e_unit type,
                  size_t column,
                  size_t line,
                  size_t player_id,
                  int hp,
                  bool played)
{
  // Sanity check: valid coordinates
  if (column >= _nbColumns || line >= _nbLines)
  {
    std::stringstream sstr;
    sstr << "In " << __PRETTY_FUNCTION__ << '\n'; /// \warning g++/clang++ only
    sstr << "Invalid provided coordinates: (" << column << ", " << line << ") "
         << "Exceed: (" << _nbColumns - 1 << ", " << _nbLines - 1 << ")";

    throw std::out_of_range(sstr.str());
  }

  // Explicitly using a shared_ptr
  std::shared_ptr<Unit> new_unit(UnitsFactory::createUnit(type));

  new_unit->setCoords({ column, line });
  new_unit->setPlayerId(player_id);
  new_unit->setHp(hp);
  new_unit->setPlayed(played);
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
    return { attacker_damages, 0 };


  // Compute defender strike-back damages
  auto att_cell = _cells[attacker.c()][attacker.l()];
  auto att_terrain = TerrainsHandler::get(att_cell->terrain());

  int dmg_def =
    static_cast<int> (defender.attackValue() / 2) - att_terrain.cover();
  auto defender_damages = std::max(1, dmg_def);


  return { attacker_damages, defender_damages };
}



e_attack_result Map::attack(std::shared_ptr<Unit> defender)
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



e_attack_result Map::attack(std::shared_ptr<Cell> target_cell)
{
  auto defender = target_cell->unit();
  if (!defender)
  {
    ERROR("Attacking empty cell");
    return e_attack_result::NONE_DIED;
  }

  return attack(defender);
}



void Map::dump(pugi::xml_document& doc)
{
  // pugi::xml_document doc;

  // Main 'map' node
  auto map = doc.append_child("map");


  // 'metadata' node
  auto metadata = map.append_child("metadata");

  // Map size
  auto map_size = metadata.append_child("map_size");
  map_size.append_attribute("nb_columns") = static_cast<int> (_nbColumns);
  map_size.append_attribute("nb_lines") = static_cast<int> (_nbLines);

  // Players
  auto players = metadata.append_child("players");

  // Current Player
  const auto player_number = game::Status::battle()->currentPlayer();
  const auto player_str = std::to_string(player_number).c_str();
  auto current_player = players.append_child("current_player");
  current_player.append_child(pugi::node_pcdata).set_value(player_str);

  for (const auto& player: game::Status::battle()->players())
  {
    auto n_player = players.append_child("player");

    auto n_color = n_player.append_child("color");
    n_color.append_attribute("r") = static_cast<int> ( player->color().r);
    n_color.append_attribute("g") = static_cast<int> (player->color().g);
    n_color.append_attribute("b") = static_cast<int> (player->color().b);

    auto n_cursor = n_player.append_child("cursor");
    n_cursor.append_attribute("col")  =
      static_cast<int> (player->cursor()->coords().c);
    n_cursor.append_attribute("line") =
      static_cast<int> (player->cursor()->coords().l);
  }


  // 'cells' node
  auto cells = map.append_child("cells");
  for (auto col(0u); col < _nbColumns; ++col)
  {
    for (auto line(0u); line < _nbLines; ++line)
    {
      auto cell = cells.append_child("cell");

      // Coordinates
      auto coords = cell.append_child("coordinates");
      coords.append_attribute("col") = col;
      coords.append_attribute("line") = line;

      // Terrain
      auto terrain_int = static_cast<int> (_cells[col][line]->terrain());
      const auto terrain_str = std::to_string(terrain_int).c_str();
      auto terrain = cell.append_child("terrain");
      terrain.append_child(pugi::node_pcdata).set_value(terrain_str);

      // Unit
      if (const auto u = _cells[col][line]->unit())
      {
        auto unit = cell.append_child("unit");
        unit.append_attribute("type") = static_cast<int> (u->type());
        unit.append_attribute("player_id") = static_cast<int> (u->playerId());
        unit.append_attribute("hp") = u->hp();
        unit.append_attribute("played") = u->played();

        // Crew
        if (u->crewSize() <= 0)
        {
          continue; // no crew -> skip to the next unit
        }

        auto crew = unit.append_child("crew");
        auto vehicle = std::static_pointer_cast<Vehicle> (u);
        for (const auto& member: vehicle->crew())
        {
          auto n = crew.append_child("member");
          n.append_attribute("role") = static_cast<int> (member.first);

          const auto& m = member.second;
          n.append_attribute("type") = static_cast<int> (m->type());
          n.append_attribute("player_id") = static_cast<int> (m->playerId());
          n.append_attribute("hp") = m->hp();
          n.append_attribute("played") = m->played();
        }
      }
    }
  }
}



void Map::stashUnit(const Unit& unit)
{
  _cells[unit.c()][unit.l()]->removeUnit();
}



void Map::stashPopUnit(const Unit& unit)
{
  newUnit(unit.type(), unit.c(), unit.l(), unit.playerId(), unit.hp(), true);
}
