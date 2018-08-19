#include <game/Battle.hh>

#include <lib/pugixml.hh>
#include <debug/Debug.hh>
#include <common/enums/units.hh>
#include <structures/Vector.hh>
#include <game/Status.hh>
#include <game/Player.hh>
#include <game/Map.hh>
#include <interface/Cursor.hh>
#include <graphics/MapGraphicsProperties.hh>



Battle::Battle() :
  _currentPlayer (0)
{
}



void Battle::initializeMap()
{
  graphics::MapGraphicsProperties::initialize();
  buildMap();
  buildPlayers();
}



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



/// \todo generate a random Map
void Battle::buildMap()
{
  _map = loadMap("map/map.xml");
}



void Battle::nextPlayer()
{
  _map->endTurn();
  ++_currentPlayer;
  _currentPlayer %= _players.size();
}



std::shared_ptr<Map> Battle::loadMap(const std::string& file_name)
{
  pugi::xml_document doc;
  if (!doc.load_file(file_name.c_str()))
  {
    ERROR("unable to load file", file_name);
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
        map->newUnit(type, col, line, player_id, hp);
      }

      cells = cells.next_sibling();
    }
  }

  return map;
}



void Battle::saveMap(const std::string& file_name)
{
  /// \todo saveMap
  std::cout << "filename: " << file_name << std::endl;
}
