/**
 * \file
 * \date December 10, 2020
 * \author Zermingore
 * \brief Inventory and ItemsContainer classes definition
 */

#include <game/Inventory.hh>

#include <game/Item.hh>
#include <graphics/Sprite.hh>
#include <graphics/GraphicsEngine.hh>
// #include <graphics/GraphicsEngine.hh>
#include <resources/ResourcesManager.hh>



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
}



void ItemsContainer::update()
{
}



void ItemsContainer::draw()
{
}



Inventory::Inventory(size_t nbCols, size_t nbLines)
  : InterfaceElement("cell_inventory_background")
  , _sprite(std::make_unique<graphics::Sprite> ("cell_inventory_background"))
  , _nbColumns(nbCols)
  , _nbLines(nbLines)
{
  graphics::Size2 size{graphics::GraphicsEngine::windowSize()};
  _sprite->setSize(size.x, size.y);
}



void Inventory::draw()
{
  _sprite->setTextureRepeat(true); // NOT in update() (reset Texture repeat)
  _sprite->draw();

  for (const auto& container: _stored)
  {
    container->draw();
  }
}
