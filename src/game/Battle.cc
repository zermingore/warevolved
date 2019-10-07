#include <game/Battle.hh>

#include <random>
#include <iomanip>
#include <stdexcept>
#include <filesystem>

#include <lib/pugixml.hh>

#include <debug/Debug.hh>
#include <tools/options/OptionsParser.hh>
#include <common/enums/units.hh>
#include <common/enums/terrains.hh>
#include <structures/Vector.hh>
#include <game/Status.hh>
#include <game/Player.hh>
#include <game/Map.hh>
#include <game/units/Unit.hh>
#include <game/units/UnitFactory.hh>
#include <game/units/Vehicle.hh>
#include <interface/Cursor.hh>
#include <graphics/MapGraphicsProperties.hh>



Battle::Battle(const OptionsParser& options_parser)
  : _currentPlayer(0)
  , _nbPlayers(0)
  , _savesDirectory("./")
  , _randomSeed(0) // randomize the seed
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
  // Unfortunately, filesystem cannot create path with trailing separator
  // Therefore, we canonize the path and trim the last separator, if any

  namespace fs = std::filesystem;
  fs::path test = _savesDirectory;
  auto dst = test.lexically_normal().string(); // clean the path
  /// \note c++20 dst.ends_with(test.preferred_separator)
  if (dst[dst.length() - 1] == test.preferred_separator)
  {
    dst.pop_back();
  }

  if (fs::exists(dst) && !fs::is_directory(dst))
  {
    /// \todo option specific exception
    throw std::runtime_error("Save path exists but is not a directory");
  }

  if (!fs::exists(dst))
  {
    NOTICE("Creating saves directory ", dst);
    fs::create_directories(dst); // may throw
    //throw std::runtime_error("not able to create it");
  }


  // Extract the random seed, if provided
  if (options_parser.optionExists("random-seed"))
  {
    _randomSeed = std::stoul(
      options_parser["random-seed"].value().arguments()[0]);
  }
}



void Battle::initializeMap()
{
  graphics::MapGraphicsProperties::initialize();
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
    loadMap();
  else
    generateRandomMap();
}



void Battle::nextPlayer()
{
  _map->endTurn();
  ++_currentPlayer;
  _currentPlayer %= _nbPlayers;
}



void Battle::generateRandomMap()
{
  // Random initialization /// \todo somewhere else
# pragma GCC diagnostic push // random_device and mt19937 are 5k on my machine
# pragma GCC diagnostic ignored "-Wlarger-than="
  std::random_device rd;
  if (!_randomSeed)
  {
    _randomSeed = rd();
  }
  NOTICE("Using random seed:", _randomSeed);
  std::mt19937 gen(_randomSeed);
# pragma GCC diagnostic pop
  std::uniform_int_distribution<> rand100(1, 100);
  std::uniform_int_distribution<> randPlayer(2, 4);
  std::uniform_int_distribution<> randMapSize(3, 15);
  std::uniform_int_distribution<> randTerrain(
    1, static_cast<int> (e_terrain::NB_TERRAIN) -1);
  std::uniform_int_distribution<> randBool(0, 1);
  std::uniform_int_distribution<> randByte(0, 255);


  // Map size
  const auto lines = randMapSize(gen);
  const auto cols = randMapSize(gen);
  NOTICE("Generating a Map of", lines, "x", cols);
  _map = std::make_shared<Map> (cols, lines);

  // Players list
  auto nb_players = randPlayer(gen);
  for (auto i = 0; i < nb_players; ++i)
  {
    // Color
    const auto r = static_cast<sf::Uint8> (randByte(gen));
    const auto g = static_cast<sf::Uint8> (randByte(gen));
    const auto b = static_cast<sf::Uint8> (randByte(gen));
    auto& p = _players.emplace_back(
      std::make_shared<Player> (graphics::Color(r, g, b)));

    // Cursor location
    std::uniform_int_distribution<> rand_col(0, cols - 1);
    std::uniform_int_distribution<> rand_line(0, lines - 1);
    p->cursor()->setCoords({ static_cast<size_t> (rand_col(gen)),
                             static_cast<size_t> (rand_line(gen)) });

    ++_nbPlayers;
  }

  // Current Player
  std::uniform_int_distribution<> randCurrentPlayer(0, nb_players - 1);
  _currentPlayer = randCurrentPlayer(gen);
  for (auto col(0); col < cols; ++col)
  {
    for (auto line(0); line < lines; ++line)
    {
      _map->setTerrain(col, line, static_cast<e_terrain> (randTerrain(gen)));
      if (rand100(gen) > 90)
      {
        auto type = e_unit::SOLDIER;
        std::uniform_int_distribution<> rand_player(0, nb_players - 1);
        auto player_id = rand_player(gen);
        auto played = false;

        // Creating an instance on the Unit only to get its max HP (I know...)
        std::shared_ptr<Unit> new_unit(UnitFactory::createUnit(type));
        auto max_hp = new_unit->maxHp();
        std::uniform_int_distribution<> randHpSoldier(1, max_hp);
        auto hp = randHpSoldier(gen);

        if (static_cast<unsigned int> (player_id) == _currentPlayer)
          played = static_cast<bool> (randBool(gen));
        _map->newUnit(type, col, line, player_id, hp, played);
      }
      if (rand100(gen) > 80)
      {
        auto type = e_unit::CAR;
        std::uniform_int_distribution<> rand_player(0, nb_players - 1);
        auto player_id = rand_player(gen);
        auto played = false;

        // Creating an instance on the Unit only to get its max HP (I know...)
        std::shared_ptr<Unit> new_unit(UnitFactory::createUnit(type));
        auto max_hp = new_unit->maxHp();
        std::uniform_int_distribution<> randHpSoldier(1, max_hp);
        auto hp = randHpSoldier(gen);

        if (static_cast<unsigned int> (player_id) == _currentPlayer)
          played = static_cast<bool> (randBool(gen));
        _map->newUnit(type, col, line, player_id, hp, played);

        // crew
        if (rand100(gen) > 40)
        {
          std::shared_ptr<Unit> member(
            UnitFactory::createUnit(e_unit::SOLDIER));

          // Fetching the unit first as we may hide it with a temporary one
          const auto unit = _map->unit(col, line);

          std::uniform_int_distribution<> randHpCrewMember(1, max_hp);
          member->setHp(randHpCrewMember(gen));
          member->setPlayed(false);
          member->setPlayerId(player_id);

          // Eventually placing a 2nd unit on a cell but move it in the vehicle
          _map->newUnit(member, 0, 0);

          auto vehicle = std::static_pointer_cast<Vehicle> (unit);
          vehicle->addToCrew(member);

          // 2nd crew member
          if (rand100(gen) > 75)
          {
            std::shared_ptr<Unit> member2(
              UnitFactory::createUnit(e_unit::SOLDIER));

            member2->setHp(randHpCrewMember(gen));
            member2->setPlayed(false);
            member2->setPlayerId(player_id);
            _map->newUnit(member2, 0, 0);

            vehicle->addToCrew(member2);
          }
        }
      }
    }
  }
}



void Battle::loadMap()
{
  pugi::xml_document doc;
  if (!doc.load_file(_loadMapFile.c_str()))
  {
    ERROR("Unable to load file", _loadMapFile);
    throw std::runtime_error("Unable to load map file; aborting...");
  }

  auto metadata = doc.child("map").child("metadata");

  // Map size
  int cols = metadata.child("map_size").attribute("nb_columns").as_int();
  int lines = metadata.child("map_size").attribute("nb_lines").as_int();
  _map = std::make_shared<Map> (cols, lines);

  // Player
  auto players = metadata.child("players");
  _currentPlayer = players.child("current_player").text().as_int();
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
    const size_t col = cursor_node.attribute("col").as_int();
    const size_t line = cursor_node.attribute("line").as_int();
    p->cursor()->setCoords({col, line});

    ++_nbPlayers;
  }

  // Cells
  auto cells = doc.child("map").child("cells");
  while (cells)
  {
    for (pugi::xml_node cell: cells.children("cell"))
    {
      // Coordinates
      int col = cell.child("coordinates").attribute("col").as_int();
      int line = cell.child("coordinates").attribute("line").as_int();

      // Terrain
      _map->setTerrain(col, line, static_cast<e_terrain> (
                        cell.child("terrain").text().as_int()));

      // Unit
      for (pugi::xml_node unit: cell.children("unit"))
      {
        auto type = static_cast<e_unit> (unit.attribute("type").as_int());
        auto player_id = unit.attribute("player_id").as_int();
        auto hp = unit.attribute("hp").as_int();
        auto played = unit.attribute("played").as_bool();
        _map->newUnit(type, col, line, player_id, hp, played);

        // Crew
        for (pugi::xml_node mbr: unit.child("crew").children("member"))
        {
          const auto u = _map->unit(col, line);
          assert(u->canHaveCrew() && "This unit cannot have a crew");

          auto t = static_cast<e_unit> (mbr.attribute("type").as_int());
          std::shared_ptr<Unit> m(UnitFactory::createUnit(t));

          m->setPlayerId(mbr.attribute("player_id").as_int());
          m->setHp(mbr.attribute("hp").as_int());
          m->setPlayed(mbr.attribute("played").as_bool());

          auto vehicle = std::static_pointer_cast<Vehicle> (u);
          u->addToCrew(m); /// \todo way to specify the role
        }
      }

      cells = cells.next_sibling();
    }
  }
}



void Battle::saveMap()
{
  pugi::xml_document doc;
  _map->dump(doc);

  // getting the current date as string
  auto now = std::chrono::system_clock::now();
  auto in_time_t = std::chrono::system_clock::to_time_t(now);
  std::stringstream ss;
  ss << std::put_time(std::localtime(&in_time_t), "%Y_%m_%d__%H_%M_%S__");

  std::string path = _savesDirectory + "/" + ss.str() + "quick_save.xml";
  std::cout << "Saving map into: " << path << std::endl;
  if (!doc.save_file(path.c_str()))
  {
    ERROR("Unable to save XML");
    return;
  }
}
