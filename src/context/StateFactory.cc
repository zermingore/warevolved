#include <context/StateFactory.hh>
#include <context/StatePlaying.hh>
#include <context/StateMovingUnit.hh>
#include <context/StateMenu.hh>
#include <common/Debug.hh>


std::shared_ptr<State> StateFactory::createState(e_state& state)
{
  Debug::printf("State: current state:", static_cast<int> (state));

  // Facto DP
  switch (state)
  {
    case e_state::PLAYING:
      return std::make_shared<StatePlaying> ();

    case e_state::MENU:
      return std::make_shared<StateMenu> ();

    case e_state::MOVING_UNIT:
      return std::make_shared<StateMovingUnit> ();

    default:
      Debug::error("UNRECOGNIZED STATE. Unable to instantiate an EventManager");
      break;
  //   MAIN_MENU,

  // SELECTION_MENU, // pick a Unit
  // MOVING_UNIT, // move it
  // ACTION_MENU, // give it an order
  // ATTACK, // ask a Unit to attack
  }

  // never reached
  return nullptr;
}
