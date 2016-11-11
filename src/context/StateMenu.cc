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
  _evtMgr->registerEvent(e_input::MOVE_UP_1, [=] { selectUp(); });
  _evtMgr->registerEvent(e_input::MOVE_DOWN_1, [=] { selectDown(); });
  _evtMgr->registerEvent(e_input::MOVE_LEFT_1, [=] { selectLeft(); });
  _evtMgr->registerEvent(e_input::MOVE_RIGHT_1, [=] { selectRight(); });

//  _evtMgr->registerEvent(e_input::SELECTION_1, [=] { validate(); });

  _evtMgr->registerEvent(e_input::EXIT_1, [=] { exit(); });


  auto player(Status::battle()->getCurrentPlayer());
  addInterfaceElement(player->menu());
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
  Debug::printf("StateMenu exit !");

  auto player(Status::battle()->getCurrentPlayer());
  player->cancel();
  Status::exitCurrentState();
}
