#include <context/StateFactory.hh>

#include <debug/Debug.hh>
#include <context/StatePlaying.hh>
#include <context/StateMovingUnit.hh>
#include <context/StateSelectTarget.hh>
#include <context/StateMenu.hh>
#include <context/StateGlobal.hh>



std::shared_ptr<State> StateFactory::createState(const e_state& state)
{
  // Factory Design Pattern
  switch (state)
  {
    case e_state::PLAYING:
      return std::make_shared<StatePlaying> ();

    // Every menu share the same State
    case e_state::MAP_MENU:
    case e_state::ACTION_MENU:
    case e_state::SELECTION_UNIT:
      return std::make_shared<StateMenu> (state);

    case e_state::MOVING_UNIT:
      return std::make_shared<StateMovingUnit> ();

    case e_state::SELECT_TARGET:
      return std::make_shared<StateSelectTarget> ();

    default:
      ERROR("UNRECOGNIZED STATE. Unable to instantiate an EventManager");
      std::exit(1);
      break;
  }

  // never reached
  return nullptr;
}
