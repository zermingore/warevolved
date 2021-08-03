/**
 * \file
 * \date August 3, 2013
 * \author Zermingore
 * \brief Battle class definition
 */

#include <game/Battle.hh>

#include <filesystem>
#include <iomanip>
#include <stdexcept>
#include <thread>

#include <lib/pugixml.hh>

#include <debug/Debug.hh>
#include <game/Map.hh>
#include <game/Player.hh>
#include <game/Status.hh>
#include <game/units/Unit.hh>
#include <game/units/UnitsFactory.hh>
#include <game/units/Vehicle.hh>
#include <graphics/Properties.hh>
#include <interface/Cursor.hh>
#include <structures/Vector.hh>
#include <tools/options/OptionsParser.hh>
#include <tools/Random.hh>



Battle::Battle(const OptionsParser& options_parser)
  : _currentPlayer(0)
  , _nbPlayers(0)
  , _savesDirectory("./saves")
{
  // Fetch the Map to load and the save directory, if provided
  if (options_parser.optionExists("load-map"))
  {
    _loadMapFile = options_parser["load-map"].value().arguments()[0];
  }
  if (options_parser.optionExists("saves-directory"))
  {
    _savesDirectory = options_parser["saves-directory"].value().arguments()[0];
  }

  // Create the saves_dir directory, if needed.
  namespace fs = std::filesystem;
  fs::path test = _savesDirectory;
  auto dst = test.lexically_normal().string(); // Canonize the path
  if (fs::exists(dst) && !fs::is_directory(dst))
  {
    throw ArgumentsException("Save path exists but is not a directory");
  }
  if (!fs::exists(dst))
  {
    NOTICE("Creating saves directory:", dst);
    if (!fs::create_directories(dst)) // may throw
    {
      throw ArgumentsException("not able to create the saves directory");
    }
  }

  Random::init(options_parser);
}



void Battle::initializeMap()
{
  buildMap();
  initializePlayers();
}



void Battle::initializePlayers()
{
  // Adjusting cursors limits /// \todo dirty
  for (const auto& player: _players)
  {
    player->cursor()->setLimits(_map->nbColumns(), _map->nbLines());
  }
}



void Battle::buildMap()
{
  if (!_loadMapFile.empty())
  {
    loadMap();
  }
  else
  {
    generateRandomMap();
  }
}



void Battle::nextPlayer()
{
  _map->endTurn();
  ++_currentPlayer;
  _currentPlayer %= _nbPlayers;
}



void Battle::generateRandomMap()
{
  // Map size
  const auto lines = Random::randVal<size_t>(3, 15);
  const auto cols = Random::randVal<size_t>(3, 15);
  NOTICE("Generating a Map of", lines, "x", cols);
  _map = std::make_shared<Map> (cols, lines);

  // Players list
  auto nb_players = Random::randVal<size_t>(2, 4);
  for (auto i = 0u; i < nb_players; ++i)
  {
    // Color
    const auto r = static_cast<sf::Uint8> (Random::randInt(0, 255));
    const auto g = static_cast<sf::Uint8> (Random::randInt(0, 255));
    const auto b = static_cast<sf::Uint8> (Random::randInt(0, 255));
    _players.emplace_back(std::make_shared<Player> (graphics::Color(r, g, b)));

    // Cursor location
    ++_nbPlayers;
  }

  // Current Player
  _currentPlayer = Random::randVal<size_t>(0, nb_players - 1);
  for (auto col(0u); col < cols; ++col)
  {
    for (auto line(0u); line < lines; ++line)
    {
      _map->setTerrain(col, line, Random::randTerrain());
      if (Random::randInt(1, 100) > 90)
      {
        auto type = e_unit::SOLDIER;
        auto player_id = Random::randVal<size_t>(0, nb_players - 1);
        auto played = false;

        auto max_hp{UnitsFactory::typeMaxHp(type)};
        auto hp = Random::randInt(1, max_hp);

        if (player_id == _currentPlayer)
        {
          played = Random::randBool();
        }
        _map->newUnit(type, col, line, player_id, hp, played);
      }
      if (Random::randInt(1, 100) > 80)
      {
        auto type = e_unit::CAR;
        auto player_id = Random::randVal<size_t>(0, nb_players - 1);
        auto played = false;

        auto max_hp{UnitsFactory::typeMaxHp(type)};
        auto hp = Random::randInt(1, max_hp);

        if (player_id == _currentPlayer)
        {
          played = Random::randBool();
        }
        _map->newUnit(type, col, line, player_id, hp, played);

        // crew
        if (Random::randInt(1, 100) > 40)
        {
          std::shared_ptr<Unit> member(
            UnitsFactory::createUnit(e_unit::SOLDIER));

          // Fetching the unit first as we may hide it with a temporary one
          const auto unit = _map->unit(col, line);

          member->setHp(Random::randInt(1, max_hp));
          member->setPlayed(false);
          member->setPlayerId(player_id);

          // Eventually placing a 2nd unit on a cell but move it in the vehicle
          _map->newUnit(member, 0, 0);

          auto vehicle = std::static_pointer_cast<Vehicle> (unit);
          vehicle->addToCrew(member);

          // 2nd crew member
          if (Random::randInt(1, 100) > 75)
          {
            std::shared_ptr<Unit> member2(
              UnitsFactory::createUnit(e_unit::SOLDIER));

            member2->setHp(Random::randInt(1, max_hp));
            member2->setPlayed(false);
            member2->setPlayerId(player_id);
            _map->newUnit(member2, 0, 0);

            vehicle->addToCrew(member2);
          }
        }
      }
    }
  }

  randomMapRefine();
}



void Battle::loadMap()
{
  pugi::xml_document doc;
  if (!doc.load_file(_loadMapFile.c_str()))
  {
    const std::string msg{"Unable to load file [" + _loadMapFile + "]"};
    ERROR(msg);
    throw std::runtime_error(msg);
  }

  auto meta = doc.child("map").child("metadata");

  // Map size
  const auto cols = meta.child("map_size").attribute("nb_columns").as_ullong();
  const auto lines = meta.child("map_size").attribute("nb_lines").as_ullong();
  _map = std::make_shared<Map> (cols, lines);

  // Player
  auto players = meta.child("players");
  _currentPlayer = players.child("current_player").text().as_ullong();
  for (auto player: players.children("player"))
  {
    // Color
    auto color_node = player.child("color");
    const auto r = static_cast<sf::Uint8> (color_node.attribute("r").as_int());
    const auto g = static_cast<sf::Uint8> (color_node.attribute("g").as_int());
    const auto b = static_cast<sf::Uint8> (color_node.attribute("b").as_int());
    auto& p = _players.emplace_back(
      std::make_shared<Player> (graphics::Color(r, g, b)));

    // Cursor location
    auto cursor_node = player.child("cursor");
    const size_t col = cursor_node.attribute("col").as_ullong();
    const size_t line = cursor_node.attribute("line").as_ullong();
    p->cursor()->setCoords({col, line});

    ++_nbPlayers;
  }

  // Cells
  auto cells = doc.child("map").child("cells");
  while (cells != nullptr)
  {
    for (pugi::xml_node cell: cells.children("cell"))
    {
      // Coordinates
      const auto col = cell.child("coordinates").attribute("col").as_ullong();
      const auto line = cell.child("coordinates").attribute("line").as_ullong();

      // Terrain
      _map->setTerrain(col, line, static_cast<e_terrain> (
                       cell.child("terrain").text().as_int()));

      // Unit
      for (pugi::xml_node unit: cell.children("unit"))
      {
        auto type = static_cast<e_unit> (unit.attribute("type").as_int());
        auto player_id = unit.attribute("player_id").as_ullong();
        auto hp = unit.attribute("hp").as_int();
        auto played = unit.attribute("played").as_bool();
        _map->newUnit(type, col, line, player_id, hp, played);

        // Crew
        for (pugi::xml_node mbr: unit.child("crew").children("member"))
        {
          auto t = static_cast<e_unit> (mbr.attribute("type").as_int());
          std::shared_ptr<Unit> m(UnitsFactory::createUnit(t));

          m->setPlayerId(mbr.attribute("player_id").as_ullong());
          m->setHp(mbr.attribute("hp").as_int());
          m->setPlayed(mbr.attribute("played").as_bool());

          const auto u = _map->unit(col, line);
          assert(u->canReceive(m) && "Cannot add this unit to a crew");
          u->addToCrew(m);
        }
      }

      cells = cells.next_sibling();
    }
  }

  // Buildings
  auto buildings = doc.child("map").child("buildings");
  while (buildings != nullptr)
  {
    for (pugi::xml_node building: buildings.children("building"))
    {
      std::vector<std::shared_ptr<Coords>> building_cells;
      for (pugi::xml_node c: building.child("cells").children("coordinates"))
      {
        const auto col = c.attribute("col").as_ullong();
        const auto line = c.attribute("line").as_ullong();
        building_cells.emplace_back(std::make_shared<Coords>(col, line));
      }
      _map->addBuilding(building_cells);
    }

    buildings = buildings.next_sibling();
  }
}



void Battle::saveMap()
{
  auto doc{_map->dump()};

  // getting the current date as string
  auto now = std::chrono::system_clock::now();
  auto in_time_t = std::chrono::system_clock::to_time_t(now);
  std::stringstream ss;
  ss << std::put_time(std::localtime(&in_time_t), "%Y_%m_%d__%H_%M_%S__");

  std::string path = _savesDirectory + "/" + ss.str() + "quick_save.xml";
  NOTICE("Saving map into: ", path);
  if (!doc->save_file(path.c_str()))
  {
    ERROR("Unable to save XML");
    return;
  }
}



void Battle::randomMapRefine()
{
  /// \todo remove and explain this sleep
  std::this_thread::sleep_for(
    std::chrono::duration<double, std::chrono::seconds::period>(1));

  // Give one extra Soldier to every player and set their cursor on it
  const auto cols{_map->nbColumns()};
  const auto lines{_map->nbLines()};
  for (const auto& player: _players)
  {
    Coords freeCoords{0, 0};
    auto found_free_cell{false};
    auto found_friendly_unit{false};
    for (auto col{0u}; col < cols && !found_friendly_unit; ++col)
    {
      for (auto line{0u}; line < lines; ++line)
      {
        // If the cell is occupied by a friendly unit, put the cursor on it
        auto unit{_map->unit(col, line)};

        if (   unit
            && unit->playerId() == player->id()
            && unit->type() == e_unit::SOLDIER)
        {
          player->cursor()->setCoords({col, line});
          unit->setPlayed(false);
          found_friendly_unit = true;
          break;
        }

        // Update the free coordinates
        if (!found_free_cell && !unit)
        {
          freeCoords = {col, line};
          found_free_cell = true;
        }
      }
    }

    // Sanity check: the map was full, without friendly unit for this player
    assert(found_free_cell || found_friendly_unit);

    // No friendly Unit found but a free Cell is available -> new Soldier
    if (found_free_cell && !found_friendly_unit)
    {
      auto max_hp{UnitsFactory::typeMaxHp(e_unit::SOLDIER)};
      _map->newUnit(e_unit::SOLDIER,
                    freeCoords.c, freeCoords.l, player->id(), max_hp, false);
      player->cursor()->setCoords({freeCoords.c, freeCoords.l});

      NOTICE("New Unit at", freeCoords.c, freeCoords.l, "for", player->id());
    }
  } // For every Player
}
