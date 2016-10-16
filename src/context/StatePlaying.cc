#include <context/StatePlaying.hh>
#include <common/enums/input.hh>
#include <input/EventManager.hh>

#include <iostream>


void test()
{
  std::cout << "test" << std::endl;
}


StatePlaying::StatePlaying()
  : State()
{
//  _eventManager = std::make_shared<EventManager> ();
  _eventManager->registerEvent(e_input::MOVE_LEFT_1, test);
}


void StatePlaying::moveCursor() // add param ?
{
  std::cout << "moveCursor()" << std::endl;
}


std::vector<int> StatePlaying::getAttrList()
{
  std::cout << "[IMPLEMENTATION ERROR] StatePlaying"
            << " Illegal call to getAttrList()"
            << std::endl;

  return std::vector<int> ();
}
