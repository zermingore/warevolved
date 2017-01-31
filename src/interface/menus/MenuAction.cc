#include <interface/menus/MenuAction.hh>
#include <interface/menus/MenuEntry.hh>
#include <common/Status.hh>
#include <game/applications/Battle.hh>


namespace interface {


MenuAction::MenuAction(e_state state, Coords clicked_cell)
  : _state(state)
  , _clickedCell(clicked_cell)
{
}


void MenuAction::build()
{
  /// \todo add condition (not moved / ...)
  if (_state == e_state::SELECTION_UNIT)
  {
    auto entry(std::make_shared<MenuEntry> (e_entry::MOVE));
    entry->setCallback( [=] { moveUnit(); });
    _entries.push_back(entry);
  }

  /// \todo add condition (not moved / ...)
  if (_state == e_state::ACTION_MENU)
  {
    PRINTF("MenuAction::build - state == ACTION_MENU");

    auto entry(std::make_shared<MenuEntry> (e_entry::WAIT));
    entry->setCallback( [=] { waitUnit(); });
    _entries.push_back(entry);
  }

  addCancelEntry( [=] { cancel(); } );
}


void MenuAction::cancel() {
  Status::clearStates();
}


void MenuAction::moveUnit() {
  Status::pushState(e_state::MOVING_UNIT);
}


void MenuAction::waitUnit()
{
  NOTICE("order: wait unit");

//  Status::battle()->map()->selectUnit(cursor_coords);
  Status::battle()->map()->moveUnit(_clickedCell);

  Status::clearStates();
}


} // namespace interface
