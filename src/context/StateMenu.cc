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
  _evtMgr->registerEvent(e_input::MOVE_UP_1,    [=] { moveUp();    });
  _evtMgr->registerEvent(e_input::MOVE_DOWN_1,  [=] { moveDown();  });
  _evtMgr->registerEvent(e_input::MOVE_LEFT_1,  [=] { moveLeft();  });
  _evtMgr->registerEvent(e_input::MOVE_RIGHT_1, [=] { moveRight(); });

  _evtMgr->registerEvent(e_input::SELECTION_1,  [=] { validate();  });
  _evtMgr->registerEvent(e_input::EXIT_1,       [=] { exit();      });
}


void StateMenu::moveUp() {
  Status::interface()->currentMenu()->moveUp();
}

void StateMenu::moveDown() {
  Status::interface()->currentMenu()->moveDown();
}

void StateMenu::moveLeft() {
  Status::interface()->currentMenu()->moveLeft();
}

void StateMenu::moveRight() {
  Status::interface()->currentMenu()->moveRight();
}


void StateMenu::validate() {
  Status::interface()->currentMenu()->validate();
}


void StateMenu::exit()
{
  // Calling the current active menu of the interface
  Status::interface()->currentMenu()->close();
  Status::exitCurrentState();
}
