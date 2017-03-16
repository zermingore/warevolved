#include <interface/menus/MenuEntry.hh>
#include <common/Status.hh>
#include <game/Battle.hh>
#include <graphics/GraphicsEngine.hh>
#include <graphics/MapGraphicsProperties.hh>


namespace interface {


MenuEntry::MenuEntry(const e_entry entry)
  : InterfaceElement("selection_menu_button")
  , _id (entry)
{
  setLabelName(entry);

  // label initialization
  _label = std::make_shared<sf::Text> ();

  /// \todo better calculus, ratio dependent, eventually, text length dependent
  using p = graphics::MapGraphicsProperties;
  _label->setCharacterSize((p::cellWidth() + p::cellHeight()) / 4);

  /// \todo set font and label using a DB
  _font = resources::ResourcesManager::getFont("font_army");
  _label->setFont(*(_font.getFont()));
  _label->setString(_labelName);
}


void MenuEntry::update()
{
  using p = graphics::MapGraphicsProperties;
  _image->setSize(p::cellWidth() * 2, p::cellHeight());
  _label->setPosition(_position.c, _position.l);
}


void MenuEntry::draw()
{
  _image->sprite()->setPosition(_position.c, _position.l);

  graphics::GraphicsEngine::draw(_label);
  graphics::GraphicsEngine::draw(_image->sprite());
}



void MenuEntry::execute() {
  _callback();
}



void MenuEntry::setLabelName(const e_entry entry)
{
  switch (entry)
  {
    case e_entry::MOVE:
      _labelName = "Move";
      break;
    case e_entry::WAIT:
      _labelName = "Wait";
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

    default:
      _labelName = "## NOT FOUND ##";
      ERROR("No label found for e_entry", static_cast<int> (entry));
      assert(!"No label found");
      break;
  }
}


} // namespace interface
