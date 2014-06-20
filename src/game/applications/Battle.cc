#include <game/applications/Battle.hh>
#include <common/Status.hh>
#include <common/globals.hh>


Battle::Battle() :
  _map (8, 8),
  _currentPlayer (0)
{
  init();
}

void Battle::init()
{
  buildPlayers();
  buildMap();
  buildUnits();
  CURSOR->setColor(_players[0]->cursorColor());
  g_interface->inGameMenu()->setBattle(this);
}

void Battle::buildPlayers()
{
  std::shared_ptr<Player> player1(new Player());
  player1->setCursorColor(Color(0, 127, 127));
  player1->setUnitsColor(Color(0, 127, 127));
  _players.push_back(player1);

  std::shared_ptr<Player> player2(new Player());
  player2->setCursorColor(Color(227, 227, 0));
  player2->setUnitsColor(Color(227, 227, 0));
  _players.push_back(player2);

  g_status->setPlayers(_players);
}

// TODO generate a random Map, read one from a file, ...
void Battle::buildMap()
{
  _map.init();
}

void Battle::buildUnits()
{
  _map.setUnit(_players[0]->newUnit(E_UNIT_SOLDIERS, 1, 1));
  _map.setUnit(_players[0]->newUnit(E_UNIT_SOLDIERS, 4, 1));

  _map.setUnit(_players[1]->newUnit(E_UNIT_SOLDIERS, 3, 4));
  _map.setUnit(_players[1]->newUnit(E_UNIT_SOLDIERS, 3, 6));
}


void Battle::nextPlayer()
{
  _players[_currentPlayer]->endTurn();
  _players[_currentPlayer++]->saveCursorPosition();
  _currentPlayer %= _players.size();
  CURSOR->setCoords(_players[_currentPlayer]->lastCursorPosition());
  CURSOR->setColor(_players[_currentPlayer]->cursorColor());
  g_status->setCurrentPlayer(_currentPlayer);
}


void Battle::run()
{
  // call from Game and manage Events ?
  // with a eventBattle class ?
}
