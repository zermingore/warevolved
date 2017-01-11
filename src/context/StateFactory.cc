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
      debug::OSD::addData("moving unit");
      return std::make_shared<StateMovingUnit> ();

    // case e_state::COMMANDING_UNIT:
    //   debug::OSD::addData("commanding unit");
    //   return std::make_shared<StateCommandingUnit> ();

    // case e_state::SELECTING_TARGET:
    //   debug::OSD::addData("selecting target");
    //   return std::make_shared<StateSelectingTarget> ();

    default:
      ERROR("UNRECOGNIZED STATE. Unable to instantiate an EventManager");
      break;
  }

  // never reached
  return nullptr;
}
