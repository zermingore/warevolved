#include <game/Battle.hh>

#include <stdexcept>
#include <filesystem>
#include <lib/pugixml.hh>
#include <debug/Debug.hh>
#include <common/enums/units.hh>
#include <structures/Vector.hh>
#include <game/Status.hh>
#include <game/Player.hh>
#include <game/Map.hh>
#include <game/units/Unit.hh>
#include <interface/Cursor.hh>
#include <graphics/MapGraphicsProperties.hh>



Battle::Battle(const OptionsParser& options_parser)
  : _currentPlayer(0)
  , _savesDirectory("./")
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
    // TODO opt exc
    throw std::runtime_error("Save path exists but is not a directory");
  }

  if (!fs::exists(dst))
  {
    NOTICE("Creating saves directory ", dst);
    fs::create_directories(dst); // may throw
    //throw std::runtime_error("not able to create it");
  }
}



void Battle::initializeMap()
{
  graphics::MapGraphicsProperties::initialize();
  buildMap();
  buildPlayers();
}



/// \todo include in buildMap()
void Battle::buildPlayers()
{
  auto player1 = std::make_shared<Player> (graphics::Color(0, 127, 127));
  _players.push_back(player1);

  auto player2 = std::make_shared<Player> (graphics::Color(227, 227, 0));
  _players.push_back(player2);

  // Adjusting cursors limits
  for (const auto& player: _players)
  {
    player->cursor()->setLimits(_map->nbColumns(), _map->nbLines());
  }
}



void Battle::buildMap()
{
  if (!_loadMapFile.empty())
    _map = loadMap();
  else
  {
    /// \todo generate a random Map
    _loadMapFile = "map/map.xml";
    _map = loadMap();
  }
}



void Battle::nextPlayer()
{
  _map->endTurn();
  ++_currentPlayer;
  _currentPlayer %= _players.size();
}



std::shared_ptr<Map> Battle::loadMap()
{
  pugi::xml_document doc;
  if (!doc.load_file(_loadMapFile.c_str()))
  {
    ERROR("unable to load file", _loadMapFile);
    return nullptr;
  }

  std::shared_ptr<Map> map; // return value
  auto metadata = doc.child("map").child("metadata");

  // Map size
  int cols = metadata.child("map_size").attribute("nb_columns").as_int();
  int lines = metadata.child("map_size").attribute("nb_lines").as_int();
  map = std::make_shared<Map> (cols, lines);

  // Current Player
  _currentPlayer = metadata.child("current_player").text().as_int();


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
      map->setTerrain(col, line, static_cast<e_terrain> (
                        cell.child("terrain").text().as_int()));

      // Unit
      for (pugi::xml_node unit: cell.children("unit"))
      {
        auto type = static_cast<e_unit> (unit.attribute("type").as_int());
        auto player_id = unit.attribute("player_id").as_int();
        auto hp = unit.attribute("hp").as_int();
        auto played = unit.attribute("played").as_bool();
        map->newUnit(type, col, line, player_id, hp, played);
      }

      cells = cells.next_sibling();
    }
  }

  return map;
}



void Battle::saveMap()
{
  pugi::xml_document doc;
  game::Status::battle()->map()->dump(doc);

  std::string path = _savesDirectory + "quick_save.xml";
  std::cout << "Saving map into: " << path << std::endl;
  if (!doc.save_file(path.c_str()))
  {
    ERROR("Unable to save XML");
    return;
  }
}
