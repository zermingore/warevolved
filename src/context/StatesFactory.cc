/**
 * \file
 * \date October 16, 2016
 * \author Zermingore
 * \brief StatesFactory class definition
 */

#include <context/StatesFactory.hh>

#include <debug/Debug.hh>
#include <context/StateEditMap.hh>
#include <context/StateGlobal.hh>
#include <context/StateMenu.hh>
#include <context/StateMenu2d.hh>
#include <context/StateMovingUnit.hh>
#include <context/StatePlaying.hh>
#include <context/StateSelectDropZone.hh>
#include <context/StateSelectTarget.hh>
#include <context/StateSelectExitZone.hh>
#include <context/StateInventory.hh>
#include <interface/menus/MenuUnitsList.hh>
#include <interface/menus/MenuUnit.hh>
#include <game/Status.hh>
#include <game/Battle.hh>
#include <game/Map.hh>
#include <game/units/Vehicle.hh>



std::unique_ptr<State> StatesFactory::createState(const e_state& state)
{
  // Factory Design Pattern
  switch (state)
  {
    case e_state::PLAYING:
      return std::make_unique<StatePlaying> ();

    case e_state::EDIT_MAP:
      return std::make_unique<StateEditMap> ();

    // These menus share the same State
    case e_state::MAP_MENU:
    case e_state::ACTION_MENU:
    case e_state::SELECTION_UNIT:
    case e_state::SELECTION_CREW:
    case e_state::BUILDING_MENU:
    case e_state::ITEM_MENU:
      return std::make_unique<StateMenu> (state);

    case e_state::CREW_MANAGEMENT:
    {
      auto menu = std::make_unique<StateMenu2d> (
        std::initializer_list<std::shared_ptr<interface::InGameMenu>> {
          std::make_shared<interface::MenuUnitsList<Vehicle>> (),
          std::make_shared<interface::MenuUnit<Vehicle>> ()
        }
      );

      auto confirmCb = [] () {
        auto selectedUnit{game::Status::battle()->map()->selectedUnit()};
        selectedUnit->setPlayed(true);

        auto v = std::static_pointer_cast<Vehicle> (selectedUnit);
        v->clearDroppedHistory();
      };
      menu->setConfirmCallback(confirmCb);

      auto cancelCb = [] () {
        // restore dropped unit
        auto selectedUnit{game::Status::battle()->map()->selectedUnit()};
        auto v = std::static_pointer_cast<Vehicle> (selectedUnit);
        v->restoreCrew();
        v->clearDroppedHistory();

        // Pop every select_drop_zone and crew_management states
        while (   game::Status::state() != e_state::ACTION_MENU
                && game::Status::state() != e_state::SELECTION_UNIT)
        {
          game::Status::popCurrentState();
        }
      };
      menu->setCancelCallback(cancelCb);

      return menu;
    }

    case e_state::BUILDING_UNITS:
    {
      auto menu = std::make_unique<StateMenu2d> (
        std::initializer_list<std::shared_ptr<interface::InGameMenu>> {
          std::make_shared<interface::MenuUnitsList<Building>> (),
          std::make_shared<interface::MenuUnit<Building>> ()
        }
      );

      auto cancelCb = [] () {
        game::Status::popCurrentState();
      };
      menu->setCancelCallback(cancelCb);

      return menu;
    }

    case e_state::MOVING_UNIT:
      return std::make_unique<StateMovingUnit> ();

    case e_state::SELECT_TARGET:
      return std::make_unique<StateSelectTarget> ();

    case e_state::SELECT_DROP_ZONE:
      return std::make_unique<StateSelectDropZone> ();

    case e_state::SELECT_EXIT_ZONE:
      return std::make_unique<StateSelectExitZone> ();

    case e_state::INVENTORY:
      return std::make_unique<StateInventory> ();

    default:
      ERROR("UNRECOGNIZED STATE. Unable to instantiate a State",
            static_cast<int> (state));
      std::exit(1);
  }

  // never reached
}
