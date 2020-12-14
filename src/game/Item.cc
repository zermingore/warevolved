/**
 * \file
 * \date December 10, 2020
 * \author Zermingore
 * \brief Item class definition
 */

#include <game/Item.hh>

#include <graphics/Sprite.hh>
#include <resources/ResourcesManager.hh>



Item::Item(const std::string& name,
           const std::string& textureName,
           size_t nbCols,
           size_t nbLines)
  : _name(name)
  , _textureName(textureName)
  , _sprite(std::make_shared<graphics::Sprite> (_textureName))
  , _nbColumns(nbCols)
  , _nbLines(nbLines)
{
}
