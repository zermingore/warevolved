#include <context/StateMenu.hh>
#include <input/EventManager.hh>
#include <common/enums/input.hh>
#include <common/Status.hh>
#include <game/applications/Battle.hh>
#include <game/Player.hh>
#include <interface/menus/InGameMenu.hh>



StateMenu::StateMenu()
{
  // browsing entries
  auto menu(Status::interface()->currentMenu());
  _evtMgr->registerEvent(e_input::MOVE_UP_1, [=] { menu->moveUp(); });
  _evtMgr->registerEvent(e_input::MOVE_DOWN_1, [=] { menu->moveDown(); });
  _evtMgr->registerEvent(e_input::MOVE_LEFT_1, [=] { menu->moveLeft(); });
  _evtMgr->registerEvent(e_input::MOVE_RIGHT_1, [=] { menu->moveRight(); });

//  _evtMgr->registerEvent(e_input::SELECTION_1, [=] { validate(); });

  _evtMgr->registerEvent(e_input::EXIT_1, [=] { exit(); });
}


void StateMenu::selectLeft()
{
  // _highlighted_entry ...
}

void StateMenu::selectRight()
{
}

void StateMenu::selectDown()
{
}

void StateMenu::selectUp()
{
}

void StateMenu::validate()
{
  // State.push(entry-> ...);
}


void StateMenu::exit()
{
  // Calling the current active menu of the interface
  Status::interface()->currentMenu()->close();
  Status::exitCurrentState();
}
