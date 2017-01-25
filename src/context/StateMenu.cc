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


void StateMenu::draw()
{
  if (_attributes.size())
  {
    auto pCoords = std::static_pointer_cast<Coords> (_attributes[0]);
    NOTICE("Coordinates:", pCoords->x, pCoords->y);
  }

  _menu->draw();
}

int StateMenu::test_void(std::shared_ptr<void> p)
{
  PRINTF("test_void here, transferring");
  test_int(std::static_pointer_cast<int> (p));

  // p = std::make_shared<int> (3);
  // std::shared_ptr<int> ip = std::static_pointer_cast<int> (p);


  // if (typeid(int) == typeid(2))
  //   NOTICE("Success");
  // else
  //   NOTICE("Failure");

//  test_int((std::make_shared<int>) (p));
//  PRINTF("test_void: VOID PTR value:", (int) (*p));
  return 0;
}

int StateMenu::test_int(std::shared_ptr<int> p)
{
  PRINTF("test_int: p value:", *p);
  return 0;
}


template<typename T>
int StateMenu::test_t(T t)
{
  if (typeid(int) == typeid(t))
    NOTICE("Success");
  else
    NOTICE("Failure");

  return 0;
}
