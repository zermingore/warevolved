#include <interface/menus/MenuAction.hh>

#include <context/State.hh>
#include <game/Status.hh>
#include <game/Battle.hh>
#include <game/Player.hh>
#include <game/units/Unit.hh>
#include <game/units/Vehicle.hh>
#include <game/PathFinding.hh>
#include <interface/Cursor.hh>
#include <interface/menus/MenuEntry.hh>

#include <debug/Debug.hh>

namespace interface {


MenuAction::MenuAction(const e_state state)
  : _state(state)
{
}


void MenuAction::build()
{
  if (_state == e_state::SELECTION_UNIT)
  {
    buildMenuSelectionUnit();
  }
  else if (_state == e_state::ACTION_MENU)
  {
    buildMenuAfterMovingUnit();
  }

  addCancelEntry([=, this] { cancel(); } );
}



void MenuAction::cancel()
{
  game::Status::clearStates();
}



bool MenuAction::allowMove()
{
  // Move forbidden if already played or move
  if (_selectedUnit->played() || _selectedUnit->moved())
  {
    return false;
  }

  // Move forbidden for a Vehicle without driver
  if (_selectedUnit->type() == e_unit::CAR)
  {
    auto v = std::static_pointer_cast<Vehicle> (_selectedUnit);
    try
    {
      v->crew().at(e_unit_role::DRIVER);
      return true;
    }
    catch (const std::out_of_range& e)
    {
      return false;
    }
  }

  return true;
}



void MenuAction::buildMenuSelectionUnit()
{
  auto map(game::Status::battle()->map());

  /// \todo use other coordinates than the menu ones
  _selectedUnit = map->unit(_coords);
  if (allowMove()
      && _selectedUnit->playerId() == game::Status::player()->id())
  {
    auto entry{std::make_shared<MenuEntry> (e_entry::MOVE)};
    entry->setCallback([=, this] { moveUnit(); });
    _entries.push_back(entry);
  }

  // add the attack entry if a target is reachable from the current position
  auto cell(map->cell(_coords));
  _pathFinding = std::make_unique<PathFinding> (_selectedUnit);
  if (!_pathFinding->getTargets(_selectedUnit, _coords)->empty())
  {
    auto entry{std::make_shared<MenuEntry> (e_entry::ATTACK)};
    entry->setCallback([=, this] { attackUnit(); });
    _entries.push_back(entry);
  }

  if (_selectedUnit->crewSize())
  {
    auto entry_crew{std::make_shared<MenuEntry> (e_entry::CREW)};
    entry_crew->setCallback([=, this] { manageCrew(); });
    _entries.push_back(entry_crew);
  }
}



void MenuAction::buildMenuAfterMovingUnit()
{
  auto map(game::Status::battle()->map());
  auto unit(map->unit(_coords));
  if (!unit) // Specific action depending on the occupation
  {
    auto entry_wait(std::make_shared<MenuEntry> (e_entry::WAIT));
    entry_wait->setCallback( [=, this] { waitUnit(); });
    _entries.push_back(entry_wait);

    /// \todo use other coordinates than the menu ones

    // _selectedUnit does not exits (another instance of MenuAction built it)
    _selectedUnit = map->selectedUnit();
    assert(_selectedUnit);
    _pathFinding = std::make_unique<PathFinding> (_selectedUnit);

    // Add the attack entry if a target is reachable from the current position
    auto cell(game::Status::battle()->map()->cell(_coords));
    if (!_pathFinding->getTargets(_selectedUnit, _coords)->empty())
    {
      auto entry(std::make_shared<MenuEntry> (e_entry::ATTACK));
      entry->setCallback( [=, this] { attackUnit(); });
      _entries.push_back(entry);
    }

    if (_selectedUnit->crewSize())
    {
      auto entry_crew(std::make_shared<MenuEntry> (e_entry::CREW));
      entry_crew->setCallback( [=, this] {
        game::Status::battle()->map()->moveUnit(_coords);
        game::Status::player()->cursor()->setCoords(_coords);
        manageCrew();
      });
      _entries.push_back(entry_crew);
    }
  }
  else
  {
    game::Status::pushState(e_state::SELECTION_CREW);
    game::Status::setStateAttributes(std::make_shared<Coords> (_coords));
    game::Status::resumeState();
  }
}


void MenuAction::moveUnit()
{
  game::Status::pushState(e_state::MOVING_UNIT);
  game::Status::resumeState();
}


void MenuAction::waitUnit()
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
  game::Status::pushState(e_state::CREW_MANAGEMENT);
  game::Status::setStateAttributes(std::make_shared<Coords> (_coords));
  game::Status::resumeState();
}



void MenuAction::attackUnit()
{
  game::Status::pushState(e_state::SELECT_TARGET);
  game::Status::setStateAttributes(std::make_shared<Coords> (_coords));
  game::Status::resumeState();
}


void MenuAction::draw()
{
  if (_pathFinding) {
    _pathFinding->drawPath();
  }

  InGameMenu::draw();
}


} // namespace interface
