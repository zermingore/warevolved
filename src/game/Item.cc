/**
 * \file
 * \date December 10, 2020
 * \author Zermingore
 * \brief Item class definition
 */

#include <game/Item.hh>

#include <graphics/Sprite.hh>
#include <resources/ResourcesManager.hh>
#include <graphics/Properties.hh>



Item::Item(const std::string& name,
           const std::string& textureName,
           size_t nbCols,
           size_t nbLines)
  : InterfaceElement(textureName)
  , _name(name)
  , _nbColumns(nbCols)
  , _nbLines(nbLines)
{
  const auto w{graphics::Properties::inventoryCellWidth()};
  const auto h{graphics::Properties::inventoryCellHeight()};

  _sprite->setSize(static_cast<float> (_nbColumns) * w,
                   static_cast<float> (_nbLines) * h);
}



void Item::update()
{
}



void Item::draw()
{
  _sprite->draw();
}
