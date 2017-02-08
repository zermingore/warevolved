#include <interface/menus/MenuAction.hh>
#include <interface/menus/MenuEntry.hh>
#include <common/Status.hh>
#include <game/applications/Battle.hh>
#include <context/State.hh>
#include <game/Player.hh>
#include <interface/Cursor.hh>
#include <game/units/Unit.hh>


namespace interface {


MenuAction::MenuAction(e_state state, Coords clicked_cell)
  : _state(state)
  , _clickedCell(clicked_cell)
{
}


void MenuAction::build()
{
  auto map(Status::battle()->map());

  if (_state == e_state::SELECTION_UNIT)
  {
    /// \todo use other coordinates as the menu ones
    auto unit(map->unit(_coords));
    if (unit->played() == false && unit->playerId() == Status::player()->id())
    {
      auto entry(std::make_shared<MenuEntry> (e_entry::MOVE));
      entry->setCallback( [=] { moveUnit(); });
      _entries.push_back(entry);
    }
  }

  /// \todo add actions (not moved / ...)
  if (_state == e_state::ACTION_MENU)
  {
    /// \todo use other coordinates as the menu ones
    // forbid to move a unit over another one
    if (!map->unit(_coords))
    {
      auto entry(std::make_shared<MenuEntry> (e_entry::WAIT));
      entry->setCallback( [=] { waitUnit(); });
      _entries.push_back(entry);
    }
  }

  addCancelEntry( [=] { cancel(); } );
}


void MenuAction::cancel() {
  Status::clearStates();
}


void MenuAction::moveUnit()
{
  Status::pushState(e_state::MOVING_UNIT);
  Status::currentState()->resume();
}


void MenuAction::waitUnit()
{
  /// \todo use other coordinates as the menu ones
  Status::battle()->map()->moveUnit(_coords);
  Status::clearStates();

  // setting the cursor over the freshly moved unit
  Status::player()->cursor()->setCoords(_coords);
}


} // namespace interface
