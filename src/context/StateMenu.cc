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
  // browsing entries
  _evtMgr->registerEvent(e_input::MOVE_UP_1,    [=] { moveUp();    });
  _evtMgr->registerEvent(e_input::MOVE_DOWN_1,  [=] { moveDown();  });

  _evtMgr->registerEvent(e_input::SELECTION_1,  [=] { validate();  });
  _evtMgr->registerEvent(e_input::EXIT_1,       [=] { exit();      });

  _menu = std::make_shared<interface::InGameMenu> ();
  _menuCoords = Status::player()->cursor()->coords();
}


void StateMenu::suspend()
{
  _menuCoords = _menu->coords();
  /// \todo save selected entry
}

void StateMenu::resume()
{
  _menu->setCoords(_menuCoords);
  _menu->build();
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
  Status::popCurrentState();
}


void StateMenu::draw() {
  _menu->draw();
}
