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
#include <resources/Text.hh>
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
  const auto w{graphics::Properties::inventoryCellWidth()};
  const auto h{graphics::Properties::inventoryCellHeight()};

  _sprite->setSize(static_cast<float> (nbCols)  * w,
                   static_cast<float> (nbLines) * h);

  _label = std::make_shared<resources::Text> (
    _name, w, graphics::Pos2(0, 0), "font_army");
}



void ItemsContainer::add(std::unique_ptr<Item> item)
{
  /// \todo Items coordinates
  Coords c{0, 0};
  _stored.push_back({c, std::move(item)});
}



void ItemsContainer::update()
{
}



void ItemsContainer::draw()
{
  const auto w{graphics::Properties::inventoryCellWidth()};
  const auto h{graphics::Properties::inventoryCellHeight()};

  // Text
  _label->setPosition(_position.x, _position.y - w);
  _label->draw();

  // Background
  _sprite->setTextureRepeat(true); // NOT in update() (reset Texture repeat)
  _sprite->setPosition(_position); // Refresh the position
  _sprite->draw();

  // Items
  for (const auto& item: _stored)
  {
    graphics::Pos2 coords(_position);
    coords.x += static_cast<float> (item.first.c) * w;
    coords.y += static_cast<float> (item.first.l) * h;

    item.second->setPosition(coords);
    item.second->draw();
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
  const sf::Color bg(127, 127, 127, 224);
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
