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
  , _selectedItemCoords(0, 0)
{
  if (nbCols <= 0 || nbLines <= 0)
  {
    _nbColumns = 0;
    _nbLines = 0;
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



std::optional<Coords> ItemsContainer::addable(Coords itemSize)
{
  if (_unlimited)
  {
    // _stored.push_back({{0, max_line}, std::move(item)});
    if (_stored.empty())
    {
      return Coords{0, 0};
    }

    const size_t last_line {
        _stored.back().first.l
      + static_cast<size_t> (_stored.back().second->size().y)
      + 1u};

    return Coords{0, last_line};
  }

  if (   (itemSize.c > _nbColumns || itemSize.l > _nbLines)
      && (itemSize.l > _nbLines   || itemSize.l > _nbColumns))
  {
    NOTICE("Item bigger as the inventory",
           itemSize.c, itemSize.l, _nbColumns, _nbLines);

    return std::nullopt;
  }


  // Locate possible new item location
  Coords loc{0, 0};
  auto location_idx{0u};
  while (location_idx < _freeCells.size())
  {
    // Find the first free Cell far enough from Container's borders
    if (   !_freeCells[location_idx]
        || location_idx % _nbColumns + itemSize.c > _nbColumns
        || location_idx % _nbLines   + itemSize.l > _nbLines)
    {
      // TODO? Optimization: skip occupied cells matching concerned item
      ++location_idx;
      continue;
    }

    // Check if every cell the Item would take is free
    auto item_fit { false };
    [&] {
      for (auto col{0u}; col < itemSize.c; ++col)
      {
        for (auto line{0u}; line < itemSize.l; ++line)
        {
          if (!_freeCells[location_idx + col + _nbColumns * line])
          {
            ++location_idx;
            return;
          }
        }
      }

      item_fit = true;
    } ();

    if (item_fit)
    {
      loc.c = location_idx % _nbColumns;
      loc.l = location_idx / _nbColumns;
      break;
    }
  }


  if (location_idx >= _freeCells.size()) // No space found
  {
    // TODO Rotate the item and try again
    return std::nullopt;
  }

  return loc;
}



bool ItemsContainer::add(std::unique_ptr<Item> item)
{
  if (!item)
  {
    ERROR("Expected Item to add");
    return false;
  }

  const auto destination { addable({ static_cast<size_t> (item->size().x),
                                     static_cast<size_t> (item->size().y)}) };

  if (!destination)
  {
    return false;
  }

  add(std::move(item), *destination);

  return true;
}



void ItemsContainer::add(std::unique_ptr<Item> item, const Coords& dst)
{
  if (!item)
  {
    ERROR("Expected Item to add");
    return;
  }

  if (_unlimited)
  {
    _stored.push_back({dst, std::move(item)});
    return;
  }

  // Keep track of free space
  auto location_idx {dst.l * _nbLines + dst.c * _nbColumns};
  for (auto col{0u}; col < static_cast<size_t> (item->size().x); ++col)
  {
    for (auto line{0u}; line < static_cast<size_t> (item->size().y); ++line)
    {
       const auto idx{location_idx + col * _nbColumns + line};
      _freeCells[idx] = false;
    }
  }

  _stored.push_back({dst, std::move(item)});
}



void ItemsContainer::update()
{
}



void ItemsContainer::draw()
{
  using namespace graphics;

  const auto w{Properties::inventoryCellWidth()};
  const auto h{Properties::inventoryCellHeight()};


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
    _sprite->setSize(static_cast<component> (cols)  * w,
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


    // Draw current selected item emphasis
    if (_drawSelectionCursor && _selectedItemCoords == itemCoords)
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


  // Container name
  if (_drawSelectionCursor)
  {
    _label->setColor(graphics::Color::Yellow);
  }
  else
  {
    _label->setColor(graphics::Color::White);
  }
  _label->setPosition(_position.x, _position.y - 2 * h);
  _label->draw();
}



void ItemsContainer::resetSelectedItem()
{
  for (auto idx_first{0u}; idx_first < _freeCells.size(); ++idx_first)
  {
    if (!_freeCells[idx_first])
    {
      _selectedItemCoords = { idx_first % _nbColumns, idx_first / _nbColumns };
      return;
    }
  }
}



e_direction ItemsContainer::selectItem(const e_direction direction)
{
  if (_stored.empty())
  {
    NOTICE("No item in the container");
    return direction;
  }


  /// \todo Moving item: don't jump to the next item but to the next cell

  // Identify best candidates for the 4 directions
  auto oriSelected {_selectedItemCoords};

  Coords itemMaxUp {0, 0};
  Coords itemMinDown {0, SIZE_MAX};
  Coords itemMaxLeft {0, 0};
  Coords itemMinRight {SIZE_MAX, 0};

  auto newItemCoords {_selectedItemCoords};
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
        _selectedItemCoords = itemMaxUp;
        return e_direction::NONE;
      }
    }

    // Down
    if (direction == e_direction::DOWN)
    {
      // Under orignal selected item and above current candidate
      if (itemCoords.l >= oriSelected.l && itemCoords.l <= itemMinDown.l)
      {
        itemMinDown = itemCoords;
        _selectedItemCoords = itemMinDown;
        return e_direction::NONE;
      }
    }

    // Left
    if (direction == e_direction::LEFT)
    {
      if (oriSelected.c <= 0)
      {
        return e_direction::LEFT;
      }

      // Left from orignal selected item and right from current candidate
      if (itemCoords.c <= oriSelected.c && itemCoords.c >= itemMaxLeft.c)
      {
        itemMaxLeft = itemCoords;
        _selectedItemCoords = itemMaxLeft;
        return e_direction::NONE;
      }
    }

    // Right
    if (direction == e_direction::RIGHT)
    {
      if (oriSelected.c + itemCoords.c >= _nbColumns)
      {
        return e_direction::RIGHT;
      }

      // Left from orignal selected item and right from current candidate
      if (itemCoords.c >= oriSelected.c && itemCoords.c <= itemMinRight.c)
      {
        itemMinRight = itemCoords;
        _selectedItemCoords = itemMinRight;
        return e_direction::NONE;
      }
    }
  }

  return e_direction::NONE;
}



void ItemsContainer::useItem()
{
  for (auto& item: _stored)
  {
    if (item.first == _selectedItemCoords)
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
    if (item.first == _selectedItemCoords)
    {
      map->cell(selectedUnit->coords())->inventory()->addEquip(
        item.second->name(),
        item.second->description(),
        static_cast<size_t> (item.second->size().x),
        static_cast<size_t> (item.second->size().y),
        item.second->slot(),
        item.second->range(),
        item.second->onUseValue()
      );

      _stored.erase(
        std::remove(_stored.begin(), _stored.end(), item), _stored.end());

      if (_unlimited)
      {
        reorganizeItems();
      }

      return;
    }
  }
}


void ItemsContainer::takeItem()
{
  auto map(game::Status::battle()->map());
  const auto selectedUnit = map->selectedUnit();
  auto cell { map->cell(selectedUnit->coords()) };

  auto item = std::move(cell->inventory()->containers()[0]->item());
  assert(item && "Cannot add NULL item");
  selectedUnit->inventory()->addEquip(std::move(item));
}



void ItemsContainer::reorganizeItems()
{
  assert(_unlimited && "Reorganization only for unlimited ItemsContainer");

  Coords newCoords {0, 0};
  for (auto& item: _stored)
  {
    item.first = newCoords;
    newCoords = { 0u, static_cast<size_t> (item.second->size().y) };
  }
}



bool ItemsContainer::selectedItemUsable()
{
  for (auto& item: _stored)
  {
    if (item.first == _selectedItemCoords)
    {
      return item.second->usable();
    }
  }

  assert(!"No Item currently selected");
  return false;
}



bool ItemsContainer::selectedItemEquippable()
{
  for (auto& item: _stored)
  {
    if (item.first == _selectedItemCoords)
    {
      return item.second->equippable();
    }
  }

  assert(!"No Item currently selected");
  return false;
}



bool ItemsContainer::empty()
{
  return _stored.empty();
}



std::unique_ptr<Item> ItemsContainer::item()
{
  for (auto& item: _stored)
  {
    if (item.first == _selectedItemCoords)
    {
      auto ptr = std::move(item.second);
      _stored.erase(
        std::remove(_stored.begin(), _stored.end(), item), _stored.end());
      return ptr;
    }
  }

  return nullptr;
}



std::map<e_item_slot, Range> ItemsContainer::range() const
{
  std::map<e_item_slot, Range> ranges;
  for (const auto& item: _stored)
  {
    ranges[item.second->slot()] = item.second->range();
  }

  return ranges;
}



size_t ItemsContainer::attackValue() const
{
  size_t secondary_weapon_damages{0u};

  for (const auto& item: _stored)
  {
    if (item.second->slot() == e_item_slot::MAIN_WEAPON)
    {
      /// \todo If usable (clip->bullets > 0)...
      return item.second->onUseValue();
    }

    if (item.second->slot() == e_item_slot::SECONDARY_WEAPON)
    {
      secondary_weapon_damages = item.second->onUseValue();
    }
  }

  return secondary_weapon_damages;
}



size_t ItemsContainer::counterAttackValue() const
{
  for (const auto& item: _stored)
  {
    if (item.second->slot() == e_item_slot::SECONDARY_WEAPON)
    {
      /// \todo If usable (clip->bullets > 0)...
      return item.second->onUseValue();
    }
  }

  return 0u;
}
