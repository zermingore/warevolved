#include <context/StatesFactory.hh>

#include <debug/Debug.hh>
#include <context/StatePlaying.hh>
#include <context/StateMovingUnit.hh>
#include <context/StateSelectTarget.hh>
#include <context/StateSelectDropZone.hh>
#include <context/StateMenu.hh>
#include <context/StateMenuCrew.hh>
#include <context/StateGlobal.hh>



std::unique_ptr<State> StatesFactory::createState(const e_state& state)
{
  // Factory Design Pattern
  switch (state)
  {
    case e_state::PLAYING:
      return std::make_unique<StatePlaying> ();

    // These menus share the same State
    case e_state::MAP_MENU:
    case e_state::ACTION_MENU:
    case e_state::SELECTION_UNIT:
    case e_state::SELECTION_CREW:
      return std::make_unique<StateMenu> (state);

    case e_state::CREW_MANAGEMENT:
      return std::make_unique<StateMenuCrew> ();

    case e_state::MOVING_UNIT:
      return std::make_unique<StateMovingUnit> ();

    case e_state::SELECT_TARGET:
      return std::make_unique<StateSelectTarget> ();

    case e_state::SELECT_DROP_ZONE:
      return std::make_unique<StateSelectDropZone> ();

    default:
      ERROR("UNRECOGNIZED STATE. Unable to instantiate an EventManager",
            static_cast<int> (state));
      std::exit(1);
  }

  // never reached
}