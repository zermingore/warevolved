#include <interface/menus/MenuAction.hh>
#include <interface/menus/MenuEntry.hh>
#include <common/Status.hh>
#include <game/Battle.hh>
#include <context/State.hh>
#include <game/Player.hh>
#include <interface/Cursor.hh>
#include <game/units/Unit.hh>
#include <game/PathFinding.hh>


namespace interface {


MenuAction::MenuAction(const e_state state, const Coords clicked_cell)
  : _state(state)
  , _clickedCell(clicked_cell)
{
}


void MenuAction::build()
{
  auto map(game::Status::battle()->map());

  if (_state == e_state::SELECTION_UNIT)
  {
    /// \todo use other coordinates than the menu ones
    _selectedUnit = map->unit(_coords);
    if (!_selectedUnit->played() && _selectedUnit->playerId()
        == game::Status::player()->id())
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
    _selectedUnit = game::Status::battle()->map()->selectedUnit();

    // add the attack entry if a target is reachable from the current position
    auto cell(game::Status::battle()->map()->cell(_coords));
    if (!target && PathFinding::getTargets(_selectedUnit, cell)->size() > 0)
    {
      auto entry(std::make_shared<MenuEntry> (e_entry::ATTACK));
      entry->setCallback( [=] { attackUnit(); });
      _entries.push_back(entry);
    }
  }

  addCancelEntry( [=] { cancel(); } );
}


void MenuAction::cancel() {
  game::Status::clearStates();
}


void MenuAction::moveUnit()
{
  game::Status::pushState(e_state::MOVING_UNIT);
  game::Status::currentState()->resume();
}


void MenuAction::waitUnit()
{
  /// \todo use other coordinates as the menu ones
  game::Status::battle()->map()->moveUnit(_coords);
  game::Status::clearStates();

  // setting the cursor over the freshly moved unit
  game::Status::player()->cursor()->setCoords(_coords);
}


void MenuAction::attackUnit()
{
  game::Status::pushState(e_state::SELECT_TARGET);
  game::Status::currentState()->setAttributes(std::make_shared<Coords> (_coords));
  game::Status::currentState()->resume();
}


void MenuAction::draw()
{
  PathFinding::drawPath();
  InGameMenu::draw();
}


} // namespace interface
