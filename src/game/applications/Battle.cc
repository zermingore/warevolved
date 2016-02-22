#include <game/applications/Battle.hh>
#include <common/structures/Vector.hh>
#include <common/Status.hh>
#include <game/Player.hh>
#include <game/Map.hh>
#include <interface/Cursor.hh>


Battle::Battle() :
  _currentPlayer (0)
{
  /// \todo map size is hard-coded
  _map = std::make_shared<Map> (this, 8, 8);
  buildPlayers();
  buildMap();
}


void Battle::buildPlayers()
{
  auto player1 = std::make_shared<Player> ();
  player1->setCursorColor(Color(0, 127, 127));
  player1->setUnitsColor(Color(0, 127, 127));
  _players.push_back(player1);

  auto player2 = std::make_shared<Player> ();
  player2->setCursorColor(Color(227, 227, 0));
  player2->setUnitsColor(Color(227, 227, 0));
  _players.push_back(player2);
}


/// \todo generate a random Map, read one from a file, ...
void Battle::buildMap()
{
  _map->initCursors();

  /// \todo delegate to a factory
  _map->newUnit(e_unit::SOLDIERS, 1, 1);
  _map->newUnit(e_unit::SOLDIERS, 4, 1);

  _map->newUnit(e_unit::SOLDIERS, 3, 4);
  _map->newUnit(e_unit::SOLDIERS, 3, 6);
}


void Battle::nextPlayer()
{
  _map->endTurn();
  ++_currentPlayer;
  _currentPlayer %= _players.size();
  //  _map->cursor(_currentPlayer)->setCoords(_players[_currentPlayer]->lastCursorPosition());
}
