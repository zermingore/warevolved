/**
 * \file
 * \date May 20, 2013
 * \author Zermingore
 * \namespace interface
 * \brief MenuEntry class definition
 */

#include <debug/Debug.hh>
#include <game/Battle.hh>
#include <game/Status.hh>
#include <graphics/GraphicsEngine.hh>
#include <graphics/Properties.hh>
#include <graphics/Sprite.hh>
#include <interface/menus/MenuEntry.hh>
#include <resources/Text.hh>


namespace interface {


MenuEntry::MenuEntry(const e_entry entry, bool wide)
  : InterfaceElement("selection_menu_button")
  , _id(entry)
  , _wide(wide)
{
  setLabelName(entry);

  const auto len { std::max(5.f, static_cast<float> (_labelName.length())) };
  const auto size { 3 * graphics::Properties::cellWidth() / len };
  _label = std::make_shared<resources::Text> (
    _labelName, size, graphics::Pos2(0, 0), "font_army");
}




MenuEntry::MenuEntry(const std::string label,
                     const graphics::Sprite &sprite,
                     const std::string notes)
  : InterfaceElement("selection_menu_button")
  , _id(e_entry::NONE)
  , _wide(true)
  , _extraSprite(std::make_shared<graphics::Sprite> (sprite))
  , _notes(notes)
{
  const auto len { std::max(5.f, static_cast<float> (_labelName.length())) };
  const auto size { 3 * graphics::Properties::cellWidth() / len };
  _label = std::make_shared<resources::Text> (
    label, size, graphics::Pos2(0, 0), "font_army");
}



void MenuEntry::update()
{
  using p = graphics::Properties;

  _lock.lock();
  if (_wide)
  {
    _sprite->setSize(p::cellWidth() * 4, p::cellHeight());
  }
  else
  {
    _sprite->setSize(p::cellWidth() * 2, p::cellHeight());
  }
  _label->setPosition(_position.x, _position.y);
  _lock.unlock();
}



void MenuEntry::draw()
{
  // Drawing the text before to have a kind of fade effect
  _label->draw();

  _sprite->setPosition(_position.x, _position.y);
  _sprite->draw();

  using p = graphics::Properties;

  if (_extraSprite)
  {
    _extraSprite->setPosition(_position.x + 2 * p::cellWidth(), _position.y);
    _extraSprite->setSize(p::cellWidth(), p::cellHeight());
    _extraSprite->draw();
  }

  if (_notes.length() > 0)
  {
    // 5: margin; 4: nb cells
    const auto text_size = (p::cellWidth() - 5 * 2) / 4;

    const graphics::Pos2 text_pos = {
      _position.x + 3 * p::cellWidth(), // 3rd cell
      _position.y
    };

    auto text = std::make_unique<resources::Text> (
      _notes, text_size, text_pos
    );
    text->draw();
  }
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
    case e_entry::CONFIRM:
      _labelName = "Confirm";
      break;

    // Buildings
    case e_entry::ENTER_BUILDING:
      _labelName = "Enter";
      break;
    case e_entry::INVESTIGATE:
      _labelName = "Investigate";
      break;
    case e_entry::CONTROL:
      _labelName = "Control";
      break;
    case e_entry::LEAVE:
      _labelName = "Leave";
      break;
    case e_entry::COLLECT:
      _labelName = "Collect";
      break;
    case e_entry::LOAD:
      _labelName = "Load";
      break;
    case e_entry::EXIT_BUILDING:
      _labelName = "Exit";
      break;

    // Items
    case e_entry::INVENTORY:
      _labelName = "Items";
      break;
    case e_entry::ITEM_USE:
      _labelName = "Use";
      break;
    case e_entry::ITEM_COMBINE:
      _labelName = "Combine";
      break;
    case e_entry::ITEM_MOVE:
      _labelName = "Move";
      break;
    case e_entry::ITEM_DROP:
      _labelName = "Drop";
      break;
    case e_entry::ITEM_TAKE:
      _labelName = "Take";
      break;
    case e_entry::ITEM_EQUIP:
      _labelName = "Equip";
      break;
    case e_entry::ITEM_UNEQUIP:
      _labelName = "Unequip";
      break;

    default:
      _labelName = "## NOT FOUND ##";
      ERROR("No label found for e_entry", debug::e_entry_string(entry));
      assert(false && "No label found");
      break;
  }
}


} // namespace interface
