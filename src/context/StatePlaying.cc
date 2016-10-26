#include <context/StatePlaying.hh>
#include <common/enums/input.hh>
#include <input/EventManager.hh>
#include <game/applications/Battle.hh>
#include <common/Status.hh>
#include <game/Player.hh>
#include <interface/Cursor.hh>

#include <iostream>



StatePlaying::StatePlaying()
  : State()
{
  // Lambda + parameter ?

  auto player(Status::battle()->getCurrentPlayer());

  // _eventManager->registerEvent(e_input::MOVE_LEFT_1, [this] {moveCursorRight});
  _evtMgr->registerEvent(e_input::MOVE_UP_1, [=] { player->moveCursorUp(); });
  _evtMgr->registerEvent(e_input::MOVE_DOWN_1, [=] { player->moveCursorDown(); });
  _evtMgr->registerEvent(e_input::MOVE_LEFT_1, [=] { player->moveCursorLeft(); });
  _evtMgr->registerEvent(e_input::MOVE_RIGHT_1, [=] { player->moveCursorRight(); });

  _evtMgr->registerEvent(e_input::SELECTION_1, [=] { player->select(); });
}


std::vector<int> StatePlaying::getAttrList()
{
  assert(! "[IMPLEMENTATION ERROR] StatePlaying Illegal call to getAttrList()");
}
