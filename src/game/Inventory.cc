/**
 * \file
 * \date December 10, 2020
 * \author Zermingore
 * \brief Inventory class definition
 */

#include <game/Inventory.hh>

#include <debug/Debug.hh>
#include <game/Item.hh>
#include <game/ItemsContainer.hh>
#include <game/Status.hh>
#include <game/Player.hh>
#include <game/PathFinding.hh> // e_direction enum
#include <graphics/Properties.hh>
#include <graphics/GraphicsEngine.hh>
#include <resources/Text.hh>
#include <interface/Cursor.hh>



Inventory::Inventory()
  : _selectedContainer(0)
{
  /// \todo Fix hard-coded sizes
  const auto sz{graphics::Properties::inventoryCellWidth()};
  _currentContainerPosition.x = 10.f * sz + 5 * sz;
}



void Inventory::draw(e_direction direction)
{
  using namespace graphics;

  // Background (only if "main" Inventory)
  if (direction == e_direction::UP)
  {
    Size2 size{GraphicsEngine::windowSize()};
    RectangleShape background(size);
    const sf::Color bg(127, 127, 127, 224);
    background.setFillColor(bg);
    GraphicsEngine::draw(background);
    game::Status::player()->cursor()->disableDrawThisFrame();
  }


  // Draw the Items inventory
  if (!_stored.empty())
  {
    Pos2 offset;
    if (direction == e_direction::UP)
    {
      offset = { Properties::gridOffsetX(), 30.f };
    }
    else if (direction == e_direction::DOWN)
    {
      offset = { Properties::gridOffsetX(),
                 static_cast<component> (GraphicsEngine::windowSize().y)
                   - Properties::gridOffsetY() };
    }

    const auto sz{Properties::inventoryCellWidth()};
    for (const auto& container: _stored)
    {
      container->setPosition(offset);
      container->draw();

      offset.x +=   sz * 2
                  + sz * static_cast<component> (std::max(
                        container->size().x, container->name().size() / 2));
    }
  }
}



void Inventory::drawInPanel(const graphics::Pos2& coords)
{
  if (_stored.empty())
  {
    return;
  }

  _stored[0]->setPosition(coords);
  _stored[0]->draw();
}



void Inventory::addContainer(e_container_type type,
                             const std::string& name,
                             int nbCols,
                             int nbLines)
{
  auto cont = std::make_unique<ItemsContainer> (type, name, nbCols, nbLines);
  cont->setPosition(_currentContainerPosition);
  _stored.emplace_back(std::move(cont));

  const auto sz{graphics::Properties::inventoryCellWidth()};
  _currentContainerPosition.x += static_cast<float> (nbCols) * sz + 5 * sz;

  for (auto& container: _stored)
  {
    container->setDrawSelectionCursor(false);
  }
  _stored.back()->setDrawSelectionCursor(true);
}



bool Inventory::addEquip(const std::string& name,
                         const std::string& description,
                         size_t nbCols,
                         size_t nbLines,
                         e_item_slot slot,
                         std::pair<std::optional<size_t>,
                                   std::optional<size_t>> range,
                         size_t onUseValue,
                         const std::function<void()>& use)
{
  auto item = std::make_unique<Item> (
    name, name, description, nbCols, nbLines, slot, range, onUseValue, use);
  return _stored[0]->add(std::move(item));
}



void Inventory::moveSelection(const e_direction direction)
{
  auto dir_container {_stored[_selectedContainer]->selectItem(direction)};

  if (dir_container == e_direction::LEFT)
  {
    _stored[_selectedContainer]->setDrawSelectionCursor(false);
    if (_selectedContainer > 0)
    {
      --_selectedContainer;
    }
    else
    {
      _selectedContainer = _stored.size() - 1;
    }
    _stored[_selectedContainer]->setDrawSelectionCursor(true);
    _stored.back()->resetSelectedItem();
  }

  if (dir_container == e_direction::RIGHT)
  {
    _stored[_selectedContainer]->setDrawSelectionCursor(false);
    _selectedContainer = (_selectedContainer + 1) % _stored.size();
    _stored[_selectedContainer]->setDrawSelectionCursor(true);
    _stored.back()->resetSelectedItem();
  }
}



void Inventory::useItem()
{
  _stored[_selectedContainer]->useItem();
}



void Inventory::dropItem()
{
  _stored[_selectedContainer]->dropItem();
}



bool Inventory::usableSelectedItem()
{
  return _stored[_selectedContainer]->selectedItemUsable();
}



bool Inventory::empty()
{
  for (const auto& container: _stored)
  {
    if (!container->empty())
    {
      return false;
    }
  }

  return true;
}



bool Inventory::equippedItem()
{
  return _stored[_selectedContainer]->type() == e_container_type::EQUIPPED;
}



bool Inventory::selectedItemEquippable()
{
  return _stored[_selectedContainer]->selectedItemEquippable();
}



void Inventory::equip()
{
  _stored[0]->add(std::move(_stored[_selectedContainer]->item()));
}



bool Inventory::unequip()
{
  auto item { _stored[_selectedContainer]->item() };
  if (!item)
  {
    ERROR("Expecting Item to unequip");
    return false;
  }


  const Coords size { static_cast<size_t> (item->size().x),
                      static_cast<size_t> (item->size().y) };

  auto equipped_list {true};
  for (auto& container: _stored)
  {
    if (equipped_list) // skip equipped list
    {
      equipped_list = false;
      continue;
    }

    const auto destination {container->addable(size)};
    if (!destination)
    {
      continue;
    }

    container->add(std::move(item), *destination);
    _stored[_selectedContainer]->reorganizeItems(); // Assumed unlimited

    NOTICE("Moved object");
    return true;
  }

  // Add the Item back if we could not add it somewhere else
  _stored[_selectedContainer]->add(std::move(item));

  return false;
}



size_t Inventory::attackValue() const
{
  return _stored[0]->attackValue();
}



size_t Inventory::counterAttackValue() const
{
  return _stored[0]->counterAttackValue();
}



std::map<e_item_slot, std::pair<std::optional<size_t>, std::optional<size_t>>>
Inventory::range() const
{
  if (_stored.empty() || _stored[0]->empty())
  {
    return {};
  }

  return _stored[0]->range();
}
