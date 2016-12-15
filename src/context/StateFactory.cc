#include <context/StateFactory.hh>
#include <context/StatePlaying.hh>
#include <context/StateMovingUnit.hh>
#include <context/StateMenu.hh>
#include <common/debug/Debug.hh>
#include <common/debug/OSD.hh>


std::shared_ptr<State> StateFactory::createState(e_state& state)
{
  // Facto DP
  switch (state)
  {
    case e_state::PLAYING:
      return std::make_shared<StatePlaying> ();

    // Every menu share the same State
    case e_state::MENU:
    case e_state::ACTION_MENU:
    case e_state::SELECTION_UNIT:
      debug::OSD::addData("menus state");
      return std::make_shared<StateMenu> ();

    case e_state::MOVING_UNIT:
      debug::OSD::addData(42);
      return std::make_shared<StateMovingUnit> ();

    default:
      Debug::error("UNRECOGNIZED STATE. Unable to instantiate an EventManager");
      break;
  }

  // never reached
  return nullptr;
}
