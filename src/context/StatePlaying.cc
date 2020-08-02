/**
 * \file
 * \date October 14, 2016
 * \author Zermingore
 * \brief StatePlaying class definition
 */

#include <context/StatePlaying.hh>

#include <common/enums/input.hh>
#include <game/Battle.hh>
#include <game/Player.hh>
#include <game/Status.hh>
#include <graphics/GraphicsEngine.hh>
#include <input/EventManager.hh>
#include <interface/Cursor.hh>



StatePlaying::StatePlaying()
{
  // Add parameters in the lambda ?
  // should these functions return booleans to consume events ?

  _evtMgr->registerEvent(e_input::MOVE_UP,
                         [=] { game::Status::player()->moveCursorUp(); });

  _evtMgr->registerEvent(e_input::MOVE_DOWN,
                         [=] { game::Status::player()->moveCursorDown(); });

  _evtMgr->registerEvent(e_input::MOVE_LEFT,
                         [=] { game::Status::player()->moveCursorLeft(); });

  _evtMgr->registerEvent(e_input::MOVE_RIGHT,
                         [=] { game::Status::player()->moveCursorRight(); });

  _evtMgr->registerEvent(e_input::SELECTION,
                         [=] { game::Status::player()->select(); });

  _evtMgr->registerEvent(e_input::EXIT,
                         [=] {
                            graphics::GraphicsEngine::exitRequest();
                         });

  addInterfaceElement(game::Status::player()->cursor());
}


void StatePlaying::draw()
{
}
