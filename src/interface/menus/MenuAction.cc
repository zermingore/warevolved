#include <interface/menus/MenuAction.hh>
#include <interface/menus/MenuEntry.hh>
#include <common/Status.hh>
#include <game/applications/Battle.hh>
#include <context/State.hh>
#include <game/Player.hh>
#include <interface/Cursor.hh>
#include <game/units/Unit.hh>
#include <game/PathFinding.hh>


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
    /// \todo use other coordinates than the menu ones
    _selectedUnit = map->unit(_coords);
    if (!_selectedUnit->played() && _selectedUnit->playerId() == Status::player()->id())
    {
      auto entry(std::make_shared<MenuEntry> (e_entry::MOVE));
      entry->setCallback( [=] { moveUnit(); });
      _entries.push_back(entry);
    }
  }

  /// \todo add actions (not moved / ...)
  if (_state == e_state::ACTION_MENU)
  {
    auto target = map->unit(_coords);

    // forbid to move a unit over another one
    if (!target) /// \todo use other coordinates as the menu ones
    {
      auto entry(std::make_shared<MenuEntry> (e_entry::WAIT));
      entry->setCallback( [=] { waitUnit(); });
      _entries.push_back(entry);
    }

    /// \todo use other coordinates than the menu ones

    // _selectedUnit does not exits (another instance of MenuAction built it)
    _selectedUnit = Status::battle()->map()->selectedUnit();

    auto path = std::make_unique<PathFinding> (Status::battle()->map());
    path->setOrigin(_coords, _selectedUnit);
    if (path->allowedAttack(_selectedUnit, _coords))
    {
      auto entry(std::make_shared<MenuEntry> (e_entry::ATTACK));
      entry->setCallback( [=] { attackUnit(target); });
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


void MenuAction::attackUnit(std::shared_ptr<Unit> target)
{
  Status::pushState(e_state::SELECT_TARGET);
  Status::currentState()->resume();

  // /// \todo add a state to select a target from the path finding
  // NOTICE("attackUnit: target will probably be invalid because not selected");

  // assert(target);

  // /// \todo give also coordinates of the holo unit (from where it attacks)
  // Status::battle()->map()->attack(target);
  // Status::clearStates();

  // /// \todo move unit

  // // setting the cursor over the attacked unit
  // Status::player()->cursor()->setCoords(_coords);
}


} // namespace interface
