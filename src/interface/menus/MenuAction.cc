#include <interface/menus/MenuAction.hh>

#include <interface/menus/MenuEntry.hh>
#include <interface/menus/MenuCrew.hh>
#include <game/Status.hh>
#include <game/Battle.hh>
#include <context/State.hh>
#include <game/Player.hh>
#include <interface/Cursor.hh>
#include <game/units/Unit.hh>
#include <game/PathFinding.hh>

#include <debug/Debug.hh>

namespace interface {


MenuAction::MenuAction(const e_state state)
  : _state(state)
{
}


void MenuAction::build()
{
  auto map(game::Status::battle()->map());

  if (_state == e_state::SELECTION_UNIT)
  {
    /// \todo use other coordinates than the menu ones
    _selectedUnit = map->unit(_coords);
    if (allowMove()
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

    if (_selectedUnit->canHaveCrew())
    {
      auto entry_crew(std::make_shared<MenuEntry> (e_entry::CREW));
      entry_crew->setCallback( [=] { manageCrew(); });
      _entries.push_back(entry_crew);
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
      game::Status::pushState(e_state::SELECTION_CREW);
      game::Status::currentState()->setAttributes(
        std::make_shared<Coords> (_coords)
      );
      game::Status::currentState()->resume();
    }
  }

  addCancelEntry( [=] { cancel(); } );
}


void MenuAction::cancel()
{
  game::Status::clearStates();
}


bool MenuAction::allowMove()
{
  return !_selectedUnit->played() && !_selectedUnit->moved();
}


void MenuAction::moveUnit()
{
  game::Status::pushState(e_state::MOVING_UNIT);
  game::Status::currentState()->resume();
}


void MenuAction::waitUnit() /// \todo forbid move; authorize grouping
{
  /// \todo use other coordinates as the menu ones
  game::Status::battle()->map()->moveUnit(_coords);
  _selectedUnit->setPlayed(true);
  game::Status::clearStates();

  // setting the cursor over the freshly moved unit
  game::Status::player()->cursor()->setCoords(_coords);
}



void MenuAction::manageCrew()
{
  game::Status::pushState(e_state::SELECTION_CREW);
  game::Status::currentState()->setAttributes(
    std::make_shared<Coords> (_coords)
  );
  game::Status::currentState()->resume();
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
