#include <context/StateFactory.hh>
#include <context/StatePlaying.hh>
#include <context/StateMovingUnit.hh>
#include <context/StateMenu.hh>
#include <common/Debug.hh>


std::shared_ptr<State> StateFactory::createState(e_state& state)
{
  PRINTF("StateFactory: creating state:", static_cast<int> (state));

  // Facto DP
  switch (state)
  {
    case e_state::PLAYING:
      return std::make_shared<StatePlaying> ();

    // Every menu share the same State
    case e_state::MENU:
    case e_state::ACTION_MENU:
    case e_state::SELECTION_UNIT:
      return std::make_shared<StateMenu> ();

    case e_state::MOVING_UNIT:
      return std::make_shared<StateMovingUnit> ();

    default:
      Debug::error("UNRECOGNIZED STATE. Unable to instantiate an EventManager");
      break;
  }

  // never reached
  return nullptr;
}
