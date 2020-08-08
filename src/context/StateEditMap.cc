/**
 * \file
 * \date April 5, 2020
 * \author Zermingore
 * \brief StateEditMap class definition
 */

#include <context/StateEditMap.hh>

#include <game/Battle.hh>
#include <game/Player.hh>
#include <game/Status.hh>
#include <graphics/GraphicsEngine.hh>
#include <input/EventManager.hh>
#include <interface/Cursor.hh>
#include <game/Map.hh>
#include <game/Cell.hh>
#include <game/units/UnitsFactory.hh>



StateEditMap::StateEditMap()
{
  // Add parameters in the lambda ?
  // should these functions return booleans to consume events ?

  auto player(game::Status::player());
  _evtMgr->registerEvent(e_input::MOVE_UP,
                         [=] { player->moveCursorUp(); });

  _evtMgr->registerEvent(e_input::MOVE_DOWN,
                         [=] { player->moveCursorDown(); });

  _evtMgr->registerEvent(e_input::MOVE_LEFT,
                         [=] { player->moveCursorLeft(); });

  _evtMgr->registerEvent(e_input::MOVE_RIGHT,
                         [=] { player->moveCursorRight(); });

  _evtMgr->registerEvent(e_input::SELECTION,
                         [=, this] { menuCell(); });

  _evtMgr->registerEvent(e_input::EXIT,
                         [=] {
                            graphics::GraphicsEngine::exitRequest();
                         });

  addInterfaceElement(player->cursor());
}


void StateEditMap::draw()
{
}


void StateEditMap::menuCell()
{
  auto map {game::Status::battle()->map()};
  auto unit {map->unit(game::Status::player()->cursor()->coords())};
  auto player {game::Status::player()};
  const auto pos {player->cursor()->coords()};

  if (unit)
  {
    map->cells()[pos.x][pos.y]->removeUnit();
  }
  else
  {
    auto hp {UnitsFactory::typeMaxHp(e_unit::SOLDIER)};
    map->newUnit(e_unit::SOLDIER, pos.x, pos.y, player->id(), hp, false);
  }
}
