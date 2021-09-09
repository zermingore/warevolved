/**
 * \file
 * \date September 8, 2021
 * \author Zermingore
 * \brief ItemsContainer class definition
 */

#include <game/ItemsContainer.hh>

#include <debug/Debug.hh>
#include <game/Battle.hh>
#include <game/Status.hh>
#include <game/Map.hh>
#include <game/Cell.hh>

#include <game/Item.hh>
#include <graphics/Sprite.hh>
#include <graphics/GraphicsEngine.hh>
#include <resources/ResourcesManager.hh>
#include <resources/Text.hh>
#include <graphics/Properties.hh>
#include <game/PathFinding.hh> // e_directions



ItemsContainer::ItemsContainer(e_container_type type,
                               const std::string& name,
                               int nbCols,
                               int nbLines)
  : InterfaceElement("cell_inventory_background")
  , _type(type)
  , _name(name)
  , _nbColumns(nbCols)
  , _nbLines(nbLines)
  , _selected(0, 0)
{
  if (nbCols <= 0 || nbLines <= 0)
  {
    _unlimited = true;
  }
  else
  {
    _freeCells.resize(_nbColumns * _nbLines, true);
  }

  using namespace graphics;

  const auto w{Properties::inventoryCellWidth()};
  const auto h{Properties::inventoryCellHeight()};

  _label = std::make_shared<resources::Text> (
    _name, w, graphics::Pos2(0, 0), "font_army");

  // Description zone
  const graphics::Pos2 location { /// \todo Consider Panel existence
    w, static_cast<component> (GraphicsEngine::windowSize().y) - 6 * h};
  _labelDescription = std::make_shared<resources::Text> (
    "Description", w, location, "font_army");
}



bool ItemsContainer::add(std::unique_ptr<Item> item)
{
  if (_unlimited)
  {
    // _stored.push_back({{0, max_line}, std::move(item)});
    if (_stored.empty())
    {
      _stored.push_back({{0, 0}, std::move(item)});
      return true;
    }
    const size_t last_line {
        _stored.back().first.l
      + static_cast<size_t> (_stored.back().second->size().y)
      + 1u};
    _stored.push_back({{0, last_line}, std::move(item)});

    return true;
  }


  const Coords sz{
    static_cast<size_t> (item->size().x),
    static_cast<size_t> (item->size().y)};

  if (   (sz.c >= _nbColumns || sz.l >= _nbLines)
      && (sz.l >= _nbLines   || sz.l >= _nbColumns))
  {
    NOTICE("Item bigger as the inventory");
    return false;
  }

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
    break;
  }


  if (location_idx >= _freeCells.size()) // No space found
  {
    // TODO Rotate the item and try again to add it
    NOTICE("Not enough space to add item", sz, location_idx);
    return false;
  }


  // Keep track of free space
  for (auto col{0u}; col < sz.c; ++col)
  {
    for (auto line{0u}; line < sz.l; ++line)
    {
       const auto idx{location_idx + col * _nbColumns + line};
      _freeCells[idx] = false;
    }
  }


  _stored.push_back({c, std::move(item)});

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
  if (_unlimited)
  {
    if (_stored.empty())
    {
      return;
    }

    const auto lines {
      _stored.back().first.l
      + static_cast<size_t> (_stored.back().second->size().y)};
    const auto cols {10u}; ///< \todo
    _sprite->setSize(static_cast<component> (cols) * w,
                     static_cast<component> (lines) * h);
  }
  else
  {
    _sprite->setSize(static_cast<component> (_nbColumns) * w,
                    static_cast<component> (_nbLines) * h);
  }
  _sprite->setTextureRepeat(true); // NOT in update() (reset Texture repeat)
  _sprite->setPosition(_position); // Refresh the position
  _sprite->draw();

  // Items
  for (const auto& item: _stored)
  {
    Coords itemCoords{ item.first.c, item.first.l };
    graphics::Pos2 coords(_position);
    coords.x += static_cast<float> (itemCoords.c) * w;
    coords.y += static_cast<float> (itemCoords.l) * h;


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
    NOTICE("No item in the container");
    return;
  }


  /// \todo Moving item: don't jump to the next item but to the next cell

  // Identify best candidates for the 4 directions
  auto oriSelected {_selected};

  Coords itemMaxUp {0, 0};
  Coords itemMinDown {0, SIZE_MAX};
  Coords itemMaxLeft {0, 0};
  Coords itemMinRight {SIZE_MAX, 0};

  auto newItemCoords {_selected};
  for (const auto& item: _stored)
  {
    const Coords itemCoords { item.first.c, item.first.l };
    if (itemCoords == oriSelected)
    {
      continue;
    }


    // Up
    if (direction == e_direction::UP)
    {
      // Above orignal selected item and under current candidate
      if (itemCoords.l <= oriSelected.l && itemCoords.l >= itemMaxUp.l)
      {
        itemMaxUp = itemCoords;
        _selected = itemMaxUp;
      }
    }

    // Down
    if (direction == e_direction::DOWN)
    {
      // Under orignal selected item and above current candidate
      if (itemCoords.l >= oriSelected.l && itemCoords.l <= itemMinDown.l)
      {
        itemMinDown = itemCoords;
        _selected = itemMinDown;
      }
    }

    // Left
    if (direction == e_direction::LEFT)
    {
      // Left from orignal selected item and right from current candidate
      if (itemCoords.c <= oriSelected.c && itemCoords.c >= itemMaxLeft.c)
      {
        itemMaxLeft = itemCoords;
        _selected = itemMaxLeft;
      }
    }

    // Right
    if (direction == e_direction::RIGHT)
    {
      // Left from orignal selected item and right from current candidate
      if (itemCoords.c >= oriSelected.c && itemCoords.c <= itemMinRight.c)
      {
        itemMinRight = itemCoords;
        _selected = itemMinRight;
      }
    }
  }
}



void ItemsContainer::useItem()
{
  for (auto& item: _stored)
  {
    if (item.first == _selected)
    {
      item.second->use();
      _stored.erase(
        std::remove(_stored.begin(), _stored.end(), item), _stored.end());
      return;
    }
  }
}



void ItemsContainer::dropItem()
{
  auto map(game::Status::battle()->map());
  const auto selectedUnit = map->selectedUnit();

  for (auto& item: _stored)
  {
    if (item.first == _selected)
    {
      map->cell(selectedUnit->coords())->inventory()->addEquip(
        item.second->name(),
        item.second->name(),
        static_cast<size_t> (item.second->size().x),
        static_cast<size_t> (item.second->size().y)
      );

      _stored.erase(
        std::remove(_stored.begin(), _stored.end(), item), _stored.end());
      return;
    }
  }
}



bool ItemsContainer::selectedItemUsable()
{
  for (auto& item: _stored)
  {
    if (item.first == _selected)
    {
      return item.second->usable();
    }
  }

  assert("No Item currently selected");
  return false;
}



bool ItemsContainer::empty()
{
  return _stored.empty();
}
