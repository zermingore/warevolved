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
#include <game/Terrain.hh>
#include <game/Inventory.hh>
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
  _inventory = false;
  switch (_state)
  {
    case e_state::SELECTION_UNIT:
      buildMenuSelectionUnit();
      break;

    case e_state::ACTION_MENU:
      buildMenuAfterMovingUnit();
      break;

    case e_state::BUILDING_MENU:
      buildMenuSelectionBuilding();
      break;

    case e_state::ITEM_MENU:
      buildMenuItem();
      break;

    default:
      break;
  }

  addCancelEntry([=, this] { cancel(); } );
}



void MenuAction::cancel()
{
  if (_selectedUnit && _selectedUnit->moved())
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

    auto entryInventory{std::make_shared<MenuEntry> (e_entry::INVENTORY)};
    entryInventory->setCallback([=, this] { openInventory(); });
    _lock.lock();
    _entries.emplace_back(std::move(entryInventory));
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

  if (   _selectedUnit->playerId() == game::Status::player()->id()
      && _selectedUnit->type() == e_unit::SOLDIER
      && cell->terrain() == e_terrain::BUILDING_DOOR)
  {
    auto entry{std::make_shared<MenuEntry> (e_entry::ENTER_BUILDING)};
    entry->setCallback([=, this] { enterBuilding(); });

    _lock.lock();
    _entries.emplace_back(std::move(entry));
    _lock.unlock();
  }

  if (!cell->inventory()->empty())
  {
    auto entry{std::make_shared<MenuEntry> (e_entry::ITEM_TAKE)};
    entry->setCallback([=, this] {
      _selectedUnit->inventory()->takeItem();
      game::Status::clearStates();
    });
    _lock.lock();
    _entries.emplace_back(std::move(entry));
    _lock.unlock();
  }
}



void MenuAction::buildMenuSelectionBuilding()
{
  auto map(game::Status::battle()->map());

  /// \todo use other coordinates than the menu ones
  auto building = map->building(_coords);
  if (   building
      && (*building)->faction()
         == static_cast<int> (game::Status::player()->id())
      && (*building)->units().size() > 0)
  {
    auto entry{std::make_shared<MenuEntry> (e_entry::EXIT_BUILDING)};
    entry->setCallback([=, this] { exitBuilding(); });

    _lock.lock();
    _entries.emplace_back(std::move(entry));
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

    if (   _selectedUnit->type() == e_unit::SOLDIER
        && cell->terrain() == e_terrain::BUILDING_DOOR)
    {
      auto entry{std::make_shared<MenuEntry> (e_entry::ENTER_BUILDING)};
      entry->setCallback([=, this] { enterBuilding(); });

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

    auto entry_wait(std::make_shared<MenuEntry> (e_entry::WAIT));
    entry_wait->setCallback([=, this] {
      waitUnit();
      game::Status::clearStates(); // will destroy 'this'
    });
    _lock.lock();
    _entries.emplace_back(std::move(entry_wait));
    _lock.unlock();


    auto entry{std::make_shared<MenuEntry> (e_entry::INVENTORY)};
    entry->setCallback([=, this] { openInventory(); });
    _lock.lock();
    _entries.emplace_back(std::move(entry));
    _lock.unlock();
  }
  else
  {
    game::Status::pushState(e_state::SELECTION_CREW);
    game::Status::setStateAttributes(std::make_shared<Coords> (_coords));
    game::Status::resumeState();
  }
}



void MenuAction::buildMenuItem()
{
  _inventory = true;
  auto map(game::Status::battle()->map());
  _selectedUnit = map->selectedUnit();
  assert(_selectedUnit);

  auto inventory{_selectedUnit->inventory()};

  if (inventory->empty() || inventory->emptySelection())
  {
    return;
  }

  if (inventory->usableSelectedItem())
  {
    auto entry{std::make_shared<MenuEntry> (e_entry::ITEM_USE)};
    entry->setCallback([=, this] {
      inventory->useItem();
      game::Status::popCurrentState();
    });
    _lock.lock();
    _entries.emplace_back(std::move(entry));
    _lock.unlock();
  }

  auto entryDrop{std::make_shared<MenuEntry> (e_entry::ITEM_DROP)};
  entryDrop->setCallback([=, this] {
    inventory->dropItem();
    game::Status::popCurrentState();
  });
  _lock.lock();
  _entries.emplace_back(std::move(entryDrop));
  _lock.unlock();

  if (inventory->selectedItemEquippable())
  {
    if (inventory->equippedItem())
    {
      auto entry{std::make_shared<MenuEntry> (e_entry::ITEM_UNEQUIP)};
      entry->setCallback([=, this] {
        inventory->unequip();
        game::Status::popCurrentState();
      });
      _lock.lock();
      _entries.emplace_back(std::move(entry));
      _lock.unlock();
    }
    else
    {
      auto entry{std::make_shared<MenuEntry> (e_entry::ITEM_EQUIP)};
      entry->setCallback([=, this] {
        inventory->equip();
        game::Status::popCurrentState();
      });
      _lock.lock();
      _entries.emplace_back(std::move(entry));
      _lock.unlock();
    }
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



void MenuAction::enterBuilding()
{
  auto map(game::Status::battle()->map());
  map->attackBuilding(_coords);
  game::Status::clearStates();
}



void MenuAction::openInventory()
{
  /// \todo Pushing the new State should not be just before switching to it?
  game::Status::pushState(e_state::INVENTORY);

  assert(_selectedUnit);

  std::vector<
    std::shared_ptr<std::pair<e_unit, std::shared_ptr<Inventory>>>> attributes;

  // Add selected Unit Inventory
  attributes.emplace_back(
    std::make_shared<std::pair<e_unit, std::shared_ptr<Inventory>>> (
      std::make_pair(_selectedUnit->type(), _selectedUnit->inventory())));

  // Add current Cell inventory
  auto cell(game::Status::battle()->map()->cell(_coords));
  attributes.emplace_back(
    std::make_shared<std::pair<e_unit, std::shared_ptr<Inventory>>> (
      std::make_pair(e_unit::NONE, /// \todo May be cleaner to use another key
                     cell->inventory())));

  // Add adjacent allies Inventories
  _pathFinding = std::make_unique<PathFinding> (_selectedUnit);
  auto adjacents { _pathFinding->getAdjacentCells(_coords) };
  for (const auto adjacent: adjacents)
  {
    const auto unit{adjacent->unit()};
    if (unit && unit->playerId() == _selectedUnit->playerId())
    {
      attributes.emplace_back(
        std::make_shared<std::pair<e_unit, std::shared_ptr<Inventory>>> (
          std::make_pair(unit->type(), unit->inventory())));
    }
  }

  // Toggle the State
  game::Status::setStateAttributes(
    std::make_shared<
      std::vector<std::shared_ptr<
        std::pair<e_unit, std::shared_ptr<Inventory>>>>> (attributes));
  game::Status::resumeState();
}



void MenuAction::exitBuilding()
{
  game::Status::pushState(e_state::BUILDING_UNITS);
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

  if (_inventory)
  {
    _selectedUnit = game::Status::battle()->map()->selectedUnit();
    assert(_selectedUnit);
    _selectedUnit->inventory()->draw(e_direction::UP);
  }

  InGameMenu::draw();
}


} // namespace interface
