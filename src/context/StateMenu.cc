#include <context/StateMenu.hh>
#include <input/EventManager.hh>
#include <common/enums/input.hh>
#include <common/Status.hh>
#include <game/applications/Battle.hh>
#include <game/Player.hh>
#include <interface/menus/Menu.hh>
#include <interface/menus/InGameMenu.hh>
#include <interface/Cursor.hh>



StateMenu::StateMenu()
  : State()
{
  _menu = std::make_shared<interface::InGameMenu> ();
  _menu->setCoords(Status::player()->cursor()->coords());
  _menu->build();

  // browsing entries
  _evtMgr->registerEvent(e_input::MOVE_UP_1,    [=] { moveUp();    });
  _evtMgr->registerEvent(e_input::MOVE_DOWN_1,  [=] { moveDown();  });

  _evtMgr->registerEvent(e_input::SELECTION_1,  [=] { validate();  });
  _evtMgr->registerEvent(e_input::EXIT_1,       [=] { exit();      });
}


void StateMenu::moveUp() {
  _menu->moveUp();
}

void StateMenu::moveDown() {
  _menu->moveDown();
}


void StateMenu::validate() {
  _menu->validate();
}


void StateMenu::exit() {
  PRINTF("poping myself...");
  Status::popCurrentState();
}


void StateMenu::draw() {
  _menu->draw();
}

// void resume
