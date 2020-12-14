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
  , _sprite(std::make_shared<graphics::Sprite> (_textureName))
{
}



Inventory::Inventory(size_t nbCols, size_t nbLines)
  : _textureName("inventory")
  , _sprite(std::make_shared<graphics::Sprite> (_textureName))
  , _nbColumns(nbCols)
  , _nbLines(nbLines)
{
}
