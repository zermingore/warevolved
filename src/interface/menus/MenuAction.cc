/**
 * \file
 * \date January 26, 2017
 * \author Zermingore
 * \namespace interface
 * \brief MenuAction class definition
 */

#include <interface/menus/MenuAction.hh>

#include <context/State.hh>
#include <game/Map.hh>
#include <game/Battle.hh>
#include <game/Cell.hh>
#include <game/PathFinding.hh>
#include <game/Player.hh>
#include <game/Status.hh>
#include <game/units/Unit.hh>
#include <game/units/Vehicle.hh>
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
  if (_selectedUnit->moved())
  {
    game::Status::player()->cursor()->setCoords(_selectedUnit->oldCoords());
    game::Status::battle()->map()->moveUnit(_selectedUnit->oldCoords());
    _selectedUnit->setMoved(false);
  }

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
  if (   _selectedUnit->type() == e_unit::CAR
      || _selectedUnit->type() == e_unit::MOTORCYCLE)
  {
    auto v = std::static_pointer_cast<Vehicle> (_selectedUnit);
    auto it = std::find_if(
      v->crew().begin(),
      v->crew().end(),
      [=] (std::pair<e_unit_role, std::shared_ptr<Unit>> member) -> bool {
        return member.first == e_unit_role::DRIVER;
      }
    );

    return it != v->crew().end();
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

    _lock.lock();
    _entries.emplace_back(std::move(entry));
    _lock.unlock();
  }

  // add the attack entry if a target is reachable from the current position
  auto cell(map->cell(_coords));
  _pathFinding = std::make_unique<PathFinding> (_selectedUnit);
  if (!_pathFinding->getTargets(_selectedUnit, _coords)->empty())
  {
    auto entry{std::make_shared<MenuEntry> (e_entry::ATTACK)};
    entry->setCallback([=, this] { attackUnit(); });

    _lock.lock();
    _entries.emplace_back(std::move(entry));
    _lock.unlock();
  }

  if (_selectedUnit->crewSize() != 0u)
  {
    auto entry_crew{std::make_shared<MenuEntry> (e_entry::CREW)};
    entry_crew->setCallback([=, this] { manageCrew(); });

    _lock.lock();
    _entries.emplace_back(std::move(entry_crew));
    _lock.unlock();
  }
}



void MenuAction::buildMenuAfterMovingUnit()
{
  /// \todo use other coordinates as the menu ones

  auto map(game::Status::battle()->map());
  auto unit(map->unit(_coords));
  if (!unit) // Specific action depending on the occupation
  {
    auto entry_wait(std::make_shared<MenuEntry> (e_entry::WAIT));
    entry_wait->setCallback([=, this] {
      waitUnit();
      game::Status::clearStates(); // will destroy 'this'
    });
    _lock.lock();
    _entries.emplace_back(std::move(entry_wait));
    _lock.unlock();

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

      _lock.lock();
      _entries.emplace_back(std::move(entry));
      _lock.unlock();
    }

    if (_selectedUnit->crewSize() != 0u)
    {
      auto entry_crew(std::make_shared<MenuEntry> (e_entry::CREW));
      entry_crew->setCallback( [=, this] {
        game::Status::battle()->map()->moveUnit(_coords);
        game::Status::player()->cursor()->setCoords(_coords);
        manageCrew();
      });

      _lock.lock();
      _entries.emplace_back(std::move(entry_crew));
      _lock.unlock();
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
  game::Status::battle()->map()->moveUnit(_coords);
  _selectedUnit->setPlayed(true);

  // setting the cursor over the freshly moved unit
  game::Status::player()->cursor()->setCoords(_coords);
}



void MenuAction::manageCrew()
{
  game::Status::pushState(e_state::CREW_MANAGEMENT);
  game::Status::setStateAttributes(
    std::make_shared<Coords> (_coords),
    std::make_shared<bool> (false));
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
