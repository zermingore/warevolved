/**
 * \file
 * \date September 21, 2019
 * \author Zermingore
 * \brief interface::MenuEntryCrew definition
 */


#include <interface/menus/MenuEntryCrew.hh>

#include <debug/Debug.hh>
#include <game/Status.hh>
#include <game/Battle.hh>
#include <graphics/Sprite.hh>
#include <graphics/GraphicsEngine.hh>
#include <graphics/MapGraphicsProperties.hh>
#include <resources/Text.hh>
#include <game/units/unit_roles.hh>


namespace interface {


MenuEntryCrew::MenuEntryCrew(e_unit_role role,
                             std::shared_ptr<const Unit> crew_member)
  : MenuEntry(e_entry::NONE)
  , _id(e_entry::NONE)
  , _crewMember(crew_member)
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
      _labelName = unit_role_str.at(_role);
      break;
  }
}


} // namespace interface
