/**
 * \file
 * \date December 10, 2020
 * \author Zermingore
 * \brief Inventory and ItemsContainer classes definition
 */

#include <game/Inventory.hh>

#include <game/Item.hh>
#include <graphics/Sprite.hh>
#include <resources/ResourcesManager.hh>



ItemsContainer::ItemsContainer(e_container_type type,
                               const std::string& name,
                               const std::string& textureName)
  : _type(type)
  , _name(name)
  , _textureName(textureName)
  , _sprite(std::make_unique<graphics::Sprite> (_textureName))
{
}



Inventory::Inventory(size_t nbCols, size_t nbLines)
  : InterfaceElement("cell_inventory_background")
  , _sprite(std::make_unique<graphics::Sprite> ("cell_inventory_background"))
  , _nbColumns(nbCols)
  , _nbLines(nbLines)
{
  _sprite->setSize(200.f, 800.f); ///< \todo Set correct size
}



void Inventory::update()
{
}



void Inventory::draw()
{
  _sprite->setTextureRepeat(true); // NOT in update() (reset Texture repeat)
  _sprite->draw();
}
