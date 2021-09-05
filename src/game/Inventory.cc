/**
 * \file
 * \date December 10, 2020
 * \author Zermingore
 * \brief Inventory and ItemsContainer classes definition
 */

#include <game/Inventory.hh>

#include <cassert>

#include <debug/Debug.hh>
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
  , _selected(0, 0)
{
  using namespace graphics;
  _freeCells.resize(_nbColumns * _nbLines, true);

  const auto w{Properties::inventoryCellWidth()};
  const auto h{Properties::inventoryCellHeight()};

  _label = std::make_shared<resources::Text> (
    _name, w, graphics::Pos2(0, 0), "font_army");

  // Description zone
  const graphics::Pos2 location {
    w, static_cast<component> (GraphicsEngine::windowSize().y) - 6 * h};
  _labelDescription = std::make_shared<resources::Text> (
    "Description", w, location, "font_army");
}



bool ItemsContainer::add(std::unique_ptr<Item> item)
{
  const Coords sz{
    static_cast<size_t> (item->size().x),
    static_cast<size_t> (item->size().y)};

  NOTICE("sz:", sz.c, sz.l);
  if (   (sz.c >= _nbColumns || sz.l >= _nbLines)
      && (sz.l >= _nbLines   || sz.l >= _nbColumns))
  {
    NOTICE("Item bigger as the inventory");
    return false;
  }
  NOTICE("sz:", sz.c, sz.l);

  // Locate possible new item location
  Coords c{0, 0};
  auto location_idx{0u};
  while (location_idx < _freeCells.size())
  {
    if (   !_freeCells[location_idx]
        || location_idx % _nbColumns + sz.c > _nbColumns
        || location_idx % _nbLines   + sz.l > _nbLines)
    {
      // TODO? Optimization: skip occupied cells matching concerned item
      ++location_idx;
      continue;
    }

    for (auto col{0u}; col < sz.c; ++col)
    {
      for (auto line{0u}; line < sz.l; ++line)
      {
        if (!_freeCells[location_idx + col * _nbColumns + line])
        {
          ++location_idx;
          continue;
        }
      }
    }

    c.c = location_idx % _nbColumns;
    c.l = location_idx / _nbColumns;
    NOTICE("location:", location_idx, "coords:", c);
    break;
  }


  if (location_idx >= _freeCells.size()) // No space found
  {
    // TODO Rotate the item and try again to add it
    NOTICE("Not enough space to add item", sz, location_idx);
    return false;
  }


  // Keep track of free space
  NOTICE("location_idx:", location_idx);

  for (auto col{0u}; col < sz.c; ++col)
  {
    for (auto line{0u}; line < sz.l; ++line)
    {
       const auto idx{location_idx + col * _nbColumns + line};
       std::cout << idx << " ";
      _freeCells[idx] = false;
    }
    std::cout << "\n";
  }


  _stored.push_back({c, std::move(item)});
  NOTICE("Added item at", c);

  return true;
}



void ItemsContainer::update()
{
}



void ItemsContainer::draw()
{
  using namespace graphics;

  const auto w{Properties::inventoryCellWidth()};
  const auto h{Properties::inventoryCellHeight()};

  // Text
  _label->setPosition(_position.x, _position.y - 2 * h);
  _label->draw();

  // Background
  _sprite->setSize(static_cast<component> (_nbColumns)  * w,
                   static_cast<component> (_nbLines) * h);
  _sprite->setTextureRepeat(true); // NOT in update() (reset Texture repeat)
  _sprite->setPosition(_position); // Refresh the position
  _sprite->draw();

  // Items
  for (const auto& item: _stored)
  {
    Coords itemCoords{ item.first.c, item.first.l };
    graphics::Pos2 coords(_position);
    coords.x += static_cast<float> (itemCoords.c) * w / 2;
    coords.y += static_cast<float> (itemCoords.l) * h / 2;


    if (_selected == itemCoords) // Current selected item
    {
      // Selection frame
      graphics::Size2 size {
        item.second->size().x * Properties::inventoryCellHeight(),
        item.second->size().y * Properties::inventoryCellWidth(),
      };

      graphics::RectangleShape background(size);
      background.setOutlineColor(graphics::Color::Yellow);
      background.setOutlineThickness(w / 4);
      background.setFillColor(graphics::Color::Transparent);
      background.setPosition(coords);
      graphics::GraphicsEngine::draw(background);


      // Description
      _labelDescription->draw();

      const auto desc{item.second->description()};
      graphics::Size2 sz { ///< \todo handle \n and length
        w * static_cast<graphics::component> (desc.length()),
        static_cast<graphics::component> (
          std::count(desc.begin(), desc.end(), '\n') + 1) * h
      };

      const graphics::Pos2 location {
        w, static_cast<component> (GraphicsEngine::windowSize().y) - 4 * h};

      graphics::RectangleShape descBg(sz);
      descBg.setPosition(location.x, location.y);
      const sf::Color bg(64, 64, 64, 255);
      descBg.setFillColor(bg);
      graphics::GraphicsEngine::draw(descBg);

      auto label = std::make_shared<resources::Text> (
        item.second->description() , w, location, "font_army");
      label->draw();
    }


    item.second->setPosition(coords);
    item.second->draw();
  }
}



void ItemsContainer::selectItem(const e_direction direction)
{
  if (_stored.empty())
  {
    return;
  }


  /// \todo Moving item: don't jump to the next item but to the next cell

  auto newItemCoords {_selected};
  for (const auto& item: _stored)
  {
    const auto coords {item.second->coords()};
    if (coords != _selected)
    {
      _selected = coords;
      return;
    }
  }
}



// _______________________________ Inventory _______________________________ //

Inventory::Inventory()
  : _equipped(std::make_unique<ItemsContainer> (
      e_container_type::EQUIPPED, "equipped", 10, 30))
  , _selectedContainer(0)
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



bool Inventory::addEquip(const std::string& name,
                         const std::string& description,
                         size_t nbCols,
                         size_t nbLines)
{
  auto item = std::make_unique<Item> (
    name, name, description, nbCols, nbLines);
  return _equipped->add(std::move(item));
}



void Inventory::moveSelection(const e_direction direction)
{
  if (_stored.empty())
  {
    return;
  }

  _stored[_selectedContainer]->selectItem(direction);
}
