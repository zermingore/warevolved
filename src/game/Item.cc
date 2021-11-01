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
           const std::string& description,
           size_t nbCols,
           size_t nbLines,
           e_item_slot slot,
           std::pair<std::optional<size_t>, std::optional<size_t>> range,
           size_t onUseValue,
           const std::function<void()>& use)
  : InterfaceElement(textureName)
  , _name(name)
  , _description(description)
  , _nbColumns(nbCols)
  , _nbLines(nbLines)
  , _slot(slot)
  , _range(range)
  , _onUseValue(onUseValue)
{
  const auto w{graphics::Properties::inventoryCellWidth()};
  const auto h{graphics::Properties::inventoryCellHeight()};

  _sprite->setSize(static_cast<float> (_nbColumns) * w,
                   static_cast<float> (_nbLines) * h);

  _use = use;
}



void Item::update()
{
}



void Item::draw()
{
  _sprite->draw();
}
