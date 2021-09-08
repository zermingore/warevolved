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
#include <graphics/Properties.hh>
#include <graphics/GraphicsEngine.hh>
#include <resources/Text.hh>
#include <game/Player.hh>
#include <interface/Cursor.hh>



Inventory::Inventory()
  : _selectedContainer(0)
{
  /// \todo Fix hard-coded sizes
  _stored.emplace_back(std::make_unique<ItemsContainer> (
      e_container_type::EQUIPPED, "equipped", 10, 30));
  _stored[0]->setPosition({10, 50});
  const auto sz{graphics::Properties::inventoryCellWidth()};
  _currentContainerPosition.x = static_cast<float> (10) * sz + 5 * sz;
}



void Inventory::draw()
{
  // Background
  graphics::Size2 size{graphics::GraphicsEngine::windowSize()};
  graphics::RectangleShape background(size);
  const sf::Color bg(127, 127, 127, 224);
  background.setFillColor(bg);
  graphics::GraphicsEngine::draw(background);
  game::Status::player()->cursor()->disableDrawThisFrame();

  for (const auto& container: _stored)
  {
    container->draw();
  }
}



void Inventory::addContainer(e_container_type type,
                             const std::string& name,
                             size_t nbCols,
                             size_t nbLines)
{
  assert(nbCols > 0 && nbLines > 0);

  auto cont = std::make_unique<ItemsContainer> (type, name, nbCols, nbLines);
  cont->setPosition(_currentContainerPosition);
  _stored.emplace_back(std::move(cont));

  const auto sz{graphics::Properties::inventoryCellWidth()};
  _currentContainerPosition.x += static_cast<float> (nbCols) * sz + 5 * sz;
}



bool Inventory::addEquip(const std::string& name,
                         const std::string& description,
                         size_t nbCols,
                         size_t nbLines,
                         const std::function<void()>& use)
{
  auto item = std::make_unique<Item> (
    name, name, description, nbCols, nbLines, use);
  return _stored[0]->add(std::move(item));
}



void Inventory::moveSelection(const e_direction direction)
{
  _stored[_selectedContainer]->selectItem(direction);
}



void Inventory::useItem()
{
  _stored[_selectedContainer]->useItem();
}



bool Inventory::usableSelectedItem()
{
  return _stored[_selectedContainer]->selectedItemUsable();
}
