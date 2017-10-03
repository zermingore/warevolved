#include <context/StatePlaying.hh>

#include <common/enums/input.hh>
#include <input/EventManager.hh>
#include <game/Battle.hh>
#include <game/Status.hh>
#include <game/Player.hh>
#include <interface/Cursor.hh>
#include <graphics/GraphicsEngine.hh>



StatePlaying::StatePlaying()
  : State()
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
                         [=] { player->select(); });

  addInterfaceElement(player->cursor());
}


void StatePlaying::draw()
{
}
