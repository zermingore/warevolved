/**
 * \file
 * \date December 10, 2020
 * \author Zermingore
 * \brief Inventory and ItemsContainer classes definition
 */

#include <game/Inventory.hh>

#include <cassert>
#include <game/Item.hh>
#include <graphics/Sprite.hh>
#include <graphics/GraphicsEngine.hh>
#include <resources/ResourcesManager.hh>
#include <graphics/Properties.hh>
#include <game/Status.hh>
#include <game/Player.hh>
#include <interface/Cursor.hh>



ItemsContainer::ItemsContainer(e_container_type type,
                               const std::string& name,
                               size_t nbCols,
                               size_t nbLines)
  : InterfaceElement("cell_inventory_background")
  , _type(type)
  , _name(name)
  , _nbColumns(nbCols)
  , _nbLines(nbLines)
{
  _sprite->setSize(
    static_cast<float> (nbCols)
     * graphics::Properties::inventoryCellWidth(),
    static_cast<float> (nbLines)
     * graphics::Properties::inventoryCellHeight());
}



void ItemsContainer::add(std::unique_ptr<Item> item)
{
  _stored.emplace_back(std::move(item));
}



void ItemsContainer::update()
{
}



void ItemsContainer::draw()
{
  _sprite->setTextureRepeat(true); // NOT in update() (reset Texture repeat)
  _sprite->setPosition(_position); // Refresh the position
  _sprite->draw();

  for (const auto& item: _stored)
  {
    item->draw();
  }
}



// _______________________________ Inventory _______________________________ //

Inventory::Inventory()
  : _equipped(std::make_unique<ItemsContainer> (
      e_container_type::EQUIPPED, "equipped", 10, 30))
{
  /// \todo Fix hard-coded sizes
  _equipped->setPosition({10, 50});
  const auto sz{graphics::Properties::inventoryCellWidth()};
  _currentContainerPosition.x = static_cast<float> (10) * sz + 5 * sz;
}



void Inventory::draw()
{
  // Background
  graphics::Size2 size{graphics::GraphicsEngine::windowSize()};
  graphics::RectangleShape background(size);
  const sf::Color bg(0, 0, 0, 224);
  background.setFillColor(bg);
  graphics::GraphicsEngine::draw(background);
  game::Status::player()->cursor()->disableDrawThisFrame();

  _equipped->draw();

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



void Inventory::addEquip(const std::string& name,
                         size_t nbCols,
                         size_t nbLines)
{
  auto item = std::make_unique<Item> (name, name, nbCols, nbLines);
  _equipped->add(std::move(item));
}