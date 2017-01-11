#include <common/Status.hh>
#include <game/applications/Battle.hh>
#include <game/units/Unit.hh>
#include <game/Player.hh>
#include <interface/Cursor.hh>
#include <interface/menus/InGameMenu.hh>
#include <interface/menus/MenuEntry.hh>
#include <common/enums/states.hh>



namespace interface {


void InGameMenu::build()
{
  PRINTF(">> ", (int) Status::state(), " <<");

  // Saving current state
  _cursor = Status::player()->cursor()->coords();
  _unit = Status::battle()->map()->unit(_coords);


  switch (Status::state())
  {
    case e_state::ACTION_MENU:
    {
      PRINTF("-= Action menu =-");
      /// \todo check if there is a target
      auto entry(std::make_shared<MenuEntry> (e_entry::WAIT));
      entry->setCallback( [=] { waitUnit(); });
      _entries.push_back(entry);
      Status::interface()->addElement(entry);

      /// \todo separate actions (move / attack / ...)
      // as they may have different cancel actions
      addCancelEntry( [=] { actionCancel(); } );
      break;
    }

    case e_state::MOVING_UNIT:
    {
      PRINTF("-= Action menu =-");
      /// \todo check if there is a target
      auto entry(std::make_shared<MenuEntry> (e_entry::WAIT));
      entry->setCallback( [=] { waitUnit(); });
      _entries.push_back(entry);
      Status::interface()->addElement(entry);

      /// \todo separate actions (move / attack / ...)
      // as they may have different cancel actions
      addCancelEntry( [=] { actionCancel(); } );
      break;
    }

    case e_state::SELECTION_UNIT:
      PRINTF("-= Selection menu =-");
      // if ((_unit = Status::battle()->map()->unit(_coords)))
      if (Status::battle()->map()->unit(_coords))
      {
        auto entry(std::make_shared<MenuEntry> (e_entry::MOVE));
        entry->setCallback( [=] { moveUnit(); });
        _entries.push_back(entry);
        Status::interface()->addElement(entry);
      }
      addCancelEntry( [=] { defaultCancel(); } );
      break;

    case e_state::PLAYING:
      /// \todo next player
      addCancelEntry( [=] { defaultCancel(); } );
      break;

    default:
      Debug::error("InGameMenu::build Invalid State:", (int) Status::state());
      std::exit(1);
      assert(!"Invalid state found building menu");
      break;
  }
}


void InGameMenu::defaultCancel() {
  Status::interface()->popMenu();
}


void InGameMenu::actionCancel()
{
  PRINTF("Canceling current action");

  // if (_unit) {
  //   _unit->setCoords(_cursor);
  // }

  // Status::interface()->popMenu();
  // Status::player()->cursor()->setCoords(_cursor);

  // from StateMovingUnit
  Status::interface()->element("cursor")->setCoords(_cursor);


  Status::interface()->clearMenu();

  while (Status::state() != e_state::PLAYING) {
    PRINTF("State:", (int) Status::state());
    Status::popCurrentState();
  }

  // purge saved data
  // _unit = nullptr;
}


void InGameMenu::addCancelEntry(std::function<void()> cancel_callback)
{
  auto entry_cancel(std::make_shared<MenuEntry> (e_entry::CANCEL));
  entry_cancel->setCallback( [=] { cancel_callback(); });
  _entries.push_back(entry_cancel);
  Status::interface()->addElement(entry_cancel);
}


void InGameMenu::moveUp() {
  incrementSelectedEntry();
}

void InGameMenu::moveDown() {
  decrementSelectedEntry();
}


void InGameMenu::validate() {
  // end validation (unit moved, ...) -> purge every menu
  _entries[_selectedEntry]->execute();
}


void InGameMenu::moveUnit()
{
  // Hiding but not deleting the current menu
  auto interface(Status::interface());
  for (auto entry: _entries) {
    interface->removeElement(entry);
  }

  // Building a new menu in the MOVING_UNIT State
  Status::pushState(e_state::MOVING_UNIT);
  // auto menu(std::make_shared<interface::InGameMenu> ());
  // menu->setCoords(_cursor);
  // menu->build();
}


void InGameMenu::waitUnit()
{
  PRINTF("order: wait unit");

  // pop every State pushed since Playing (select, move unit)
  while (Status::state() != e_state::PLAYING) {
    Status::popCurrentState();
  }

  // Removing the interface elements of this menu
  for (auto entry: _entries) {
    Status::interface()->removeElement(entry);
  }

  // clearing the menu stack
  Status::interface()->clearMenu();
}


void InGameMenu::update(const std::shared_ptr<Map::MapGraphicsProperties> properties)
{
  auto width(properties->cellWidth());
  auto height(properties->cellHeight());

  // _coords is filled by the player, with cursor coordinates
  _position.x = _coords.x * width  + properties->gridOffsetX();
  _position.y = _coords.y * height + properties->gridOffsetY();

  // highlighting current selection
  Coords selected_entry_pos(_position.x, _position.y + height * _selectedEntry);
  _imageSelection.setPosition(selected_entry_pos);

  // update entries positions
  auto entry_index(0);
  for (auto entry: _entries)
  {
    entry->setPosition(Coords(_position.x, _position.y + height * entry_index));
    ++entry_index;
  }
}


/// \todo move in Dtor ?
void InGameMenu::close()
{
  auto interface(Status::interface());
  for (auto entry: _entries) {
    interface->removeElement(entry);
  }
  // interface->removeElement(this); // apparently not needed, not sure why
}


void InGameMenu::draw() {
  _imageSelection.draw();
}


} // namespace interface
