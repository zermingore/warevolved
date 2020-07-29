/**
 * \file
 * \date September 21, 2019
 * \author Zermingore
 * \brief interface::MenuEntryCrew definition
 */


#include <interface/menus/MenuEntryCrew.hh>

#include <debug/Debug.hh>
#include <game/Battle.hh>
#include <game/Status.hh>
#include <game/Player.hh>
#include <game/units/Vehicle.hh>
#include <game/units/unit_roles.hh>
#include <graphics/GraphicsEngine.hh>
#include <graphics/MapGraphicsProperties.hh>
#include <graphics/Sprite.hh>
#include <resources/Text.hh>
#include <utility>
#include <utility>


namespace interface {


MenuEntryCrew::MenuEntryCrew(e_unit_role role,
                             std::shared_ptr<const Unit> crew_member)
  : MenuEntry(e_entry::NONE)
  , _id(e_entry::NONE)
  , _crewMember(std::move(std::move(crew_member)))
  , _role(role)
{
  setLabelName();

  // label initialization
  /// \todo the size should be ratio dependent, eventually text length dependent
  using p = graphics::MapGraphicsProperties;
  auto size { (p::cellWidth() / 2 + p::cellHeight()) / 4 };

  _label = std::make_shared<resources::Text> (
    _labelName, size, graphics::Pos2(0, 0), "font_army");
}



MenuEntryCrew::MenuEntryCrew(const e_entry entry)
  : MenuEntry(entry)
  , _id(entry)
  , _crewMember(nullptr)
  , _role(e_unit_role::NONE)
{
  setLabelName();

  // label initialization
  /// \todo the size should be ratio dependent, eventually text length dependent
  using p = graphics::MapGraphicsProperties;
  auto size { (p::cellWidth() / 2 + p::cellHeight()) / 4 };

  _label = std::make_shared<resources::Text> (
    _labelName, size, graphics::Pos2(0, 0), "font_army");
}



void MenuEntryCrew::update()
{
  using p = graphics::MapGraphicsProperties;
  _sprite->setSize(p::cellWidth() * 4, p::cellHeight());
  _label->setPosition(_position.x + 2, _position.y);
}



void MenuEntryCrew::draw()
{
  // Drawing the text before to have a kind of fade effect
  _label->draw();

  _sprite->setPosition(_position.x, _position.y);
  _sprite->draw();

  // If any, draw the Unit and some of its statistics
  if (_role != e_unit_role::NONE) // Cancel / Confirm don't apply
  {
    // Unit Sprite
    const auto selected_unit(game::Status::battle()->map()->selectedUnit());
    const auto vehicle = std::static_pointer_cast<Vehicle> (selected_unit);
    const auto dropping_unit = vehicle->crew().at(_role);

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



void MenuEntryCrew::execute()
{
  for (const auto& callback: _callbacks)
  {
    callback();
  }
}



void MenuEntryCrew::setLabelName()
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
      _labelName = UNIT_ROLE_STR.at(_role);
      break;
  }
}


} // namespace interface
