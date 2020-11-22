/**
 * \file
 * \date November 22, 2020
 * \author Zermingore
 * \namespace interface
 * \brief MenuEntryBuildingUnit definition
 */

#include <interface/menus/MenuEntryBuildingUnit.hh>

#include <debug/Debug.hh>
#include <game/Map.hh>
#include <game/Battle.hh>
#include <game/Status.hh>
#include <game/Player.hh>
#include <game/Building.hh>
#include <graphics/GraphicsEngine.hh>
#include <graphics/MapGraphicsProperties.hh>
#include <graphics/Sprite.hh>
#include <resources/Text.hh>

namespace interface {


MenuEntryBuildingUnit::MenuEntryBuildingUnit(
  const e_entry entry,
  std::shared_ptr<Building> building,
  int crew_idx)
    : MenuEntry(entry)
    , _building(building)
    , _crewIdx(crew_idx)
{
  setLabelName();

  // label initialization
  /// \todo the size should be ratio dependent, eventually text length dependent
  using p = graphics::MapGraphicsProperties;
  auto size { (p::cellWidth() / 2 + p::cellHeight()) / 4 };

  _label = std::make_shared<resources::Text> (
    _labelName, size, graphics::Pos2(0, 0), "font_army");
}



void MenuEntryBuildingUnit::update()
{
  using p = graphics::MapGraphicsProperties;
  _lock.lock();
  _sprite->setSize(p::cellWidth() * 4, p::cellHeight());
  _label->setPosition(_position.x + 2, _position.y);
  _lock.unlock();
}



void MenuEntryBuildingUnit::draw()
{
  // Drawing the text before to have a kind of fade effect
  _label->draw();

  _sprite->setPosition(_position.x, _position.y);
  _sprite->draw();

  // If any, draw the Unit and some of its statistics
  if (_crewIdx != -1) // Cancel / Confirm don't apply
  {
    // Unit Sprite
    const auto dropping_unit =
      _building->getUnits()[static_cast<size_t> (_crewIdx)];

    const auto sprite_unit(dropping_unit->sprite());
    using p = graphics::MapGraphicsProperties;

    sprite_unit->setPosition(_position.x + 2 * p::cellWidth(), _position.y);
    sprite_unit->setSize(p::cellWidth(), p::cellHeight());
    sprite_unit->setColor(game::Status::player()->color());
    sprite_unit->draw();


    // Unit statistics
    const auto& unit_data =
    "hp:     " + std::to_string(dropping_unit->hp())          + '\n' +
    "attack: " + std::to_string(dropping_unit->attackValue());

    // 5: margin; 4: nb cells
    const auto text_size = (p::cellWidth() - 5 * 2) / 4;

    const graphics::Pos2 text_pos = {
      _position.x + 3 * p::cellWidth(), // 3rd cell
      _position.y
    };

    auto text = std::make_unique<resources::Text> (
      unit_data, text_size, text_pos
    );
    text->draw();
  }
}



void MenuEntryBuildingUnit::execute() const
{
  for (const auto& callback: _callbacks)
  {
    callback();
  }
}



void MenuEntryBuildingUnit::setLabelName()
{
  /// \todo set string using a DB
  switch (_id)
  {
    case e_entry::CANCEL:
      _labelName = "Cancel";
      return;

    case e_entry::CREW_CONFIRM:
      _labelName = "Confirm";
      return;

    default:
      _labelName = "Unit";
      break;
  }
}


} // namespace interface
