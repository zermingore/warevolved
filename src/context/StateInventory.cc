/**
 * \file
 * \date December 6, 2020
 * \author Zermingore
 * \brief StateInventory class implementation
 */

#include <cassert>

#include <context/StateInventory.hh>

#include <debug/Debug.hh>
#include <context/StateMenu.hh>
#include <game/Cell.hh>
#include <game/Map.hh>
#include <game/Battle.hh>
#include <game/PathFinding.hh>
#include <game/Player.hh>
#include <game/Status.hh>
#include <game/units/Unit.hh>
#include <game/Inventory.hh>
#include <graphics/GraphicsEngine.hh>
#include <graphics/Properties.hh>
#include <graphics/Sprite.hh>
#include <graphics/graphic_types.hh>
#include <input/EventManager.hh>
#include <interface/Cursor.hh>
#include <interface/Interface.hh>
#include <interface/menus/InGameMenu.hh>



StateInventory::StateInventory()
  : _cursorCoords({0, 0})
{
  // used to get the cursor's coordinates and access to the callbacks
  auto player(game::Status::player());

  // we need a selected unit to continue
  player->updateSelectedUnit();

  _evtMgr->registerEvent(e_input::MOVE_UP,    [=, this] { selectUp();    });
  _evtMgr->registerEvent(e_input::MOVE_DOWN,  [=, this] { selectDown();  });
  _evtMgr->registerEvent(e_input::MOVE_LEFT,  [=, this] { selectLeft();  });
  _evtMgr->registerEvent(e_input::MOVE_RIGHT, [=, this] { selectRight(); });

  _evtMgr->registerEvent(e_input::SELECTION,  [=, this] {
      game::Status::pushState(e_state::ITEM_MENU);
      // game::Status::setStateAttributes() /// \todo give item / item index
      game::Status::resumeState();
  });

  _evtMgr->registerEvent(e_input::EXIT, [=, this] { exit(); });

  // Graphical attributes initialization
  auto map { game::Status::battle()->map() };
  auto cursor_coords { player->cursor()->coords() };
}



void StateInventory::exit()
{
  game::Status::popCurrentState();
}



void StateInventory::resume()
{
  // Retrieve the concerned Inventories in the attributes
  fetchAttributes();
}



void StateInventory::selectUp()
{
  _inventories[_currentInventory]->moveSelection(e_direction::UP);
}

void StateInventory::selectDown()
{
  _inventories[_currentInventory]->moveSelection(e_direction::DOWN);
}

void StateInventory::selectLeft()
{
  _inventories[_currentInventory]->moveSelection(e_direction::LEFT);
}

void StateInventory::selectRight()
{
  _inventories[_currentInventory]->moveSelection(e_direction::RIGHT);
}



void StateInventory::draw()
{
  _inventories[0]->draw(e_direction::UP);
  _inventories[1]->draw(e_direction::DOWN);

  /// \todo Inventories of adjacent allied Units
}



void StateInventory::fetchAttributes()
{
  if (_attributes.empty())
  {
    ERROR("StateInventory::fetchAttributes called without attributes");
    assert(false);
    return;
  }


  // Fetch the Inventory \todo properly handle attributes
  auto attrVector = std::static_pointer_cast<
        std::vector<std::shared_ptr<
          std::pair<e_unit, std::shared_ptr<Inventory>>>>> (
            _attributes[0]);

  if (attrVector->size() < 2)
  {
    ERROR("StateInventory::fetchAttributes missing expected attributes");
    assert(false);
    return;
  }

  for (auto attribute: *attrVector)
  {
    _inventories.push_back(attribute->second);
  }

  // reset the attributes vector
  _attributes.clear();
}
