#include <debug/Debug.hh>
#include <game/Battle.hh>
#include <game/Status.hh>
#include <graphics/GraphicsEngine.hh>
#include <graphics/MapGraphicsProperties.hh>
#include <graphics/Sprite.hh>
#include <interface/menus/MenuEntry.hh>
#include <resources/Text.hh>


namespace interface {


MenuEntry::MenuEntry(const e_entry entry)
  : InterfaceElement("selection_menu_button")
  , _id (entry)
{
  setLabelName(entry);

  // label initialization
  /// \todo the size should be ratio dependent, eventually text length dependent
  using p = graphics::MapGraphicsProperties;
  auto size { (p::cellWidth() + p::cellHeight()) / 4 };

  _label = std::make_shared<resources::Text> (
    _labelName, size, graphics::Pos2(0, 0), "font_army");
}



void MenuEntry::update()
{
  using p = graphics::MapGraphicsProperties;
  _sprite->setSize(p::cellWidth() * 2, p::cellHeight());
  _label->setPosition(_position.x, _position.y);
}



void MenuEntry::draw()
{
  // Drawing the text before to have a kind of fade effect
  _label->draw();

  _sprite->setPosition(_position.x, _position.y);
  _sprite->draw();
}



void MenuEntry::execute()
{
  for (const auto& callback: _callbacks)
  {
    callback();
  }
}



void MenuEntry::setLabelName(const e_entry entry)
{
  /// \todo set string using a DB
  switch (entry)
  {
    case e_entry::NONE:
      _labelName = "Invalid";
      break;
    case e_entry::MOVE:
      _labelName = "Move";
      break;
    case e_entry::WAIT:
      _labelName = "Wait";
      break;
    case e_entry::PICK_UP:
      _labelName = "Pick\n  Up";
      break;
    case e_entry::CREW:
      _labelName = "Crew";
      break;
    case e_entry::BOARD:
      _labelName = "Board";
      break;
    case e_entry::DROP_OFF:
      _labelName = "Drop\n  Off";
      break;
    case e_entry::GET_OUT:
      _labelName = "Get\n  Out";
      break;
    case e_entry::NEXT_TURN:
      _labelName = "Next\n  Turn";
      break;
    case e_entry::ATTACK:
      _labelName = "Attack";
      break;
    case e_entry::CANCEL:
      _labelName = "Cancel";
      break;
    case e_entry::CREW_CONFIRM:
      _labelName = "Confirm";
      break;

    default:
      _labelName = "## NOT FOUND ##";
      ERROR("No label found for e_entry", static_cast<int> (entry));
      assert(false && "No label found");
      break;
  }
}


} // namespace interface
