#include <context/StatePlaying.hh>
#include <common/enums/input.hh>
#include <input/EventManager.hh>
#include <game/applications/Battle.hh>
#include <common/Status.hh>
#include <game/Player.hh>
#include <interface/Cursor.hh>

#include <iostream>


void test()
{
  std::cout << "test" << std::endl;
}


StatePlaying::StatePlaying()
  : State()
{
  // Lambda + parameter ?
  // _eventManager->registerEvent(e_input::MOVE_LEFT_1, [this] {moveCursorRight});
  _eventManager->registerEvent(e_input::MOVE_UP_1,
                               std::bind(&StatePlaying::moveCursorUp, this));

  _eventManager->registerEvent(e_input::MOVE_DOWN_1,
                               std::bind(&StatePlaying::moveCursorDown, this));

  _eventManager->registerEvent(e_input::MOVE_LEFT_1,
                               std::bind(&StatePlaying::moveCursorLeft, this));

  _eventManager->registerEvent(e_input::MOVE_RIGHT_1,
                               std::bind(&StatePlaying::moveCursorRight, this));
  // _eventManager->registerEvent(e_input::MOVE_RIGHT_1,
  //                              std::bind(&Status::battle()->getCurrentPlayer()->moveCursorRight, Status::battle()));
}


void StatePlaying::moveCursorLeft()
{
//  const auto cursor(Status::battle()->getCurrentPlayer()->moveCursorLeft());
}


void StatePlaying::moveCursorRight()
{
  Status::battle()->getCurrentPlayer()->moveCursorRight();
//  const auto cursor(Status::battle()->getCurrentPlayer()->moveCursorRight());
}


void StatePlaying::moveCursorUp()
{
  const auto cursor(Status::battle()->getCurrentPlayer()->interface());
//  cursor->moveUp();
}

void StatePlaying::moveCursorDown()
{
  const auto cursor(Status::battle()->getCurrentPlayer()->interface());
//  cursor->moveDown();
}


std::vector<int> StatePlaying::getAttrList()
{
  std::cout << "[IMPLEMENTATION ERROR] StatePlaying"
            << " Illegal call to getAttrList()"
            << std::endl;

  // std::static_assert(false);

  return std::vector<int> ();
}
