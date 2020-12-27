/**
 * \file
 * \date December 1st, 2020
 * \author Zermingore
 * \namespace interface
 * \brief MenuUnit templates definition
 */

#include <interface/menus/MenuUnit.hh>

#include <debug/Debug.hh>
#include <context/State.hh>
#include <game/Map.hh>
#include <game/Battle.hh>
#include <game/PathFinding.hh>
#include <game/Player.hh>
#include <game/Status.hh>
#include <game/units/Vehicle.hh>
#include <graphics/Properties.hh>
#include <interface/Cursor.hh>



namespace interface {


template<typename T>
void MenuUnit<T>::build()
{
  auto map(game::Status::battle()->map());
  const auto selectedUnit = map->selectedUnit();
  auto vehicle = std::static_pointer_cast<Vehicle> (selectedUnit);

  _lock.lock();
  _entries.clear();
  _lock.unlock();

  // Add a get_out entry only if the unit can exit the vehicle
  PathFinding path(vehicle);
  const auto freeDropZones = path.getDropZones(vehicle->coords());
  if (!freeDropZones.empty())
  {
    auto entry(std::make_shared<MenuEntry> (e_entry::GET_OUT));
    entry->setCallbacks(
    {
      [=, this] { getOut(); },
    });

    _lock.lock();
    _entries.emplace_back(std::move(entry));
    _lock.unlock();
  }

  addCancelEntry( [=, this] { cancel(); } );
}



template<typename T>
void MenuUnit<T>::draw()
{
  update();

  _lock.lock();
  for (const auto& entry: _entries)
  {
    entry->draw();
  }
  _lock.unlock();

  _imageSelection->draw();
}



template<typename T>
void MenuUnit<T>::getOut()
{
  auto coords(game::Status::player()->cellCursorPosition());
  if (std::is_same<T, Building>::value)
  {
    game::Status::pushState(e_state::SELECT_EXIT_ZONE);
    game::Status::setStateAttributes(
      std::make_shared<Coords> (coords),
      std::make_shared<size_t> (_unitIdx)
    );
  }
  else if (std::is_same<T, Vehicle>::value)
  {
    game::Status::pushState(e_state::SELECT_DROP_ZONE);
    game::Status::setStateAttributes(
      std::make_shared<Coords> (coords),
      std::make_shared<e_unit_role> (_role),
      std::make_shared<size_t> (_unitIdx)
    );
  }
  else
  {
    ERROR("MenuUnit: Invalid container type");
    return;
  }

  game::Status::resumeState();
}


} // namespace interface
