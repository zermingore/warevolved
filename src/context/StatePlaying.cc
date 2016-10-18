#include <context/StatePlaying.hh>
#include <common/enums/input.hh>
#include <input/EventManager.hh>
#include <game/applications/Battle.hh>

#include <iostream>


void test()
{
  std::cout << "test" << std::endl;
}


StatePlaying::StatePlaying()
  : State()
{
  _eventManager->registerEvent(e_input::MOVE_LEFT_1,
                               std::bind(&StatePlaying::moveCursorLeft, this));
}


void StatePlaying::moveCursorLeft()
{
  std::cout << "moveCursor()" << std::endl;
}


std::vector<int> StatePlaying::getAttrList()
{
  std::cout << "[IMPLEMENTATION ERROR] StatePlaying"
            << " Illegal call to getAttrList()"
            << std::endl;

  // std::static_assert(false);

  return std::vector<int> ();
}
