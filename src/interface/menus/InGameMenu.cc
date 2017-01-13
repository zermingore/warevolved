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
  _cursorCoords = Status::player()->cursor()->coords();
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

      /// \todo separate actions (move / attack / ...)
      // as they may have different cancel actions
      /// Could add a flag in the state: restoration point
      /// -> pop until restoration point
      /// (and execute resume function -> default selected entry)
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

  PRINTF("nb entries:", _entries.size());
}


void InGameMenu::defaultCancel() {
  Status::popCurrentState();
}


void InGameMenu::actionCancel()
{
  PRINTF("Canceling current action");

  // from StateMovingUnit
  // Status::interface()->element("cursor")->setCoords(_cursorCoords);

  Status::clearStates();

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
  // Building a new menu in the MOVING_UNIT State
  Status::pushState(e_state::MOVING_UNIT);
}


void InGameMenu::waitUnit()
{
  PRINTF("order: wait unit");
  ERROR("TODO move unit");

  /// \todo move unit
  // Status::battle()->map()->moveUnit(_selectedUnit, _cursorCoords);
  Status::clearStates();
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
    entry->update(properties);
    ++entry_index;
  }
}


/// \todo move in Dtor ?
void InGameMenu::close()
{
  // auto interface(Status::interface());
  // for (auto entry: _entries) {
  //   interface->removeElement(entry);
  // }

  // interface->removeElement(this); // apparently not needed, not sure why
}


void InGameMenu::draw() {
  update(Status::battle()->map()->graphicsProperties());

  for (auto entry: _entries) {
    entry->draw();
    std::cout << ".";
  }
  std::cout << std::endl;

  _imageSelection.draw();
}


} // namespace interface
