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
#include <resources/ResourcesManager.hh>
#include <graphics/MapGraphicsProperties.hh>
#include <game/Status.hh>
#include <game/Player.hh>
#include <interface/Cursor.hh>



ItemsContainer::ItemsContainer(e_container_type type,
                               const std::string& name,
                               size_t nbCols,
                               size_t nbLines)
  : InterfaceElement("cell_inventory_background")
  , _sprite(std::make_unique<graphics::Sprite> ("cell_inventory_background"))
  , _type(type)
  , _name(name)
  , _nbColumns(nbCols)
  , _nbLines(nbLines)
{
  _sprite->setSize(
    static_cast<float> (nbCols)
     * graphics::MapGraphicsProperties::inventoryCellHeight(),
    static_cast<float> (nbLines)
     * graphics::MapGraphicsProperties::inventoryCellWidth());
}



void ItemsContainer::update()
{
}



void ItemsContainer::draw()
{
  _sprite->setTextureRepeat(true); // NOT in update() (reset Texture repeat)
  _sprite->draw();
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

  // _sprite->setTextureRepeat(true); // NOT in update() (reset Texture repeat)
  // _sprite->draw();

  for (const auto& container: _stored)
  {
    container->draw();
  }
}
