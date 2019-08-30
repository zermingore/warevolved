#include <interface/menus/MenuAction.hh>
#include <interface/menus/MenuEntry.hh>
#include <game/Status.hh>
#include <game/Battle.hh>
#include <context/State.hh>
#include <game/Player.hh>
#include <interface/Cursor.hh>
#include <game/units/Unit.hh>
#include <game/units/Vehicle.hh>
#include <game/PathFinding.hh>

#include <debug/Debug.hh>

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
    if (!_selectedUnit->played()
        && _selectedUnit->playerId() == game::Status::player()->id())
    {
      auto entry(std::make_shared<MenuEntry> (e_entry::MOVE));
      entry->setCallback( [=] { moveUnit(); });
      _entries.push_back(entry);
    }

    // add the attack entry if a target is reachable from the current position
    auto cell(map->cell(_coords));
    _pathFinding = std::make_unique<PathFinding> (_selectedUnit);
    if (_pathFinding->getTargets(_selectedUnit, _coords)->size() > 0)
    {
      auto entry(std::make_shared<MenuEntry> (e_entry::ATTACK));
      entry->setCallback( [=] { attackUnit(); });
      _entries.push_back(entry);
    }
  }

  if (_state == e_state::ACTION_MENU)
  {
    auto unit(map->unit(_coords));
    if (!unit) // Forbidding to do an action on an occupied Cell
    {
      auto entry_wait(std::make_shared<MenuEntry> (e_entry::WAIT));
      entry_wait->setCallback( [=] { waitUnit(); });
      _entries.push_back(entry_wait);

      /// \todo use other coordinates than the menu ones

      // _selectedUnit does not exits (another instance of MenuAction built it)
      _selectedUnit = map->selectedUnit();
      assert(_selectedUnit);
      _pathFinding = std::make_unique<PathFinding> (_selectedUnit);

      // Add the attack entry if a target is reachable from the current position
      auto cell(game::Status::battle()->map()->cell(_coords));
      if (_pathFinding->getTargets(_selectedUnit, _coords)->size() > 0)
      {
        auto entry(std::make_shared<MenuEntry> (e_entry::ATTACK));
        entry->setCallback( [=] { attackUnit(); });
        _entries.push_back(entry);
      }
    }
    else
    {
      _selectedUnit = map->selectedUnit();
      if (_selectedUnit->playerId() == unit->playerId())
      {
        if (_selectedUnit->type() == e_unit::CAR && unit->type() == e_unit::SOLDIERS)
        {
          auto entry_group(std::make_shared<MenuEntry> (e_entry::PICK_UP));
          entry_group->setCallback(
			[=] { _selectedUnit->addToCrew(unit); });
          _entries.push_back(entry_group);
        }
        else if (_selectedUnit->type() == e_unit::SOLDIERS && unit->type() == e_unit::CAR)
        {
          auto entry_group(std::make_shared<MenuEntry> (e_entry::BOARD));
          entry_group->setCallback(
			[=] { unit->addToCrew(_selectedUnit); });
          _entries.push_back(entry_group);
        }
      }
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
  game::Status::currentState()->setAttributes(
    std::make_shared<Coords> (_coords));

  game::Status::currentState()->resume();
}


void MenuAction::draw()
{
  if (_pathFinding) {
    _pathFinding->drawPath();
  }

  InGameMenu::draw();
}


} // namespace interface
