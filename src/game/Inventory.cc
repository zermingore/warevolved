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
  _sprite->setPosition(0, 0);
  _sprite->setSize(50.f, 50.f);
}



Inventory::Inventory(size_t nbCols, size_t nbLines)
  : InterfaceElement("inventory")
  , _sprite(std::make_unique<graphics::Sprite> ("inventory_background"))
  , _nbColumns(nbCols)
  , _nbLines(nbLines)
{
  _sprite->setPosition(0, 0);
  _sprite->setSize(200.f, 200.f);
}



void Inventory::update()
{
}

void Inventory::draw()
{
  _sprite->draw();
}
