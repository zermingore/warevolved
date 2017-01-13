#include <interface/menus/MenuEntry.hh>
#include <common/Status.hh>
#include <game/applications/Battle.hh>
#include <graphics/GraphicsEngine.hh>


namespace interface {


MenuEntry::MenuEntry(e_entry entry)
  : InterfaceElement("selection_menu_button")
  , _id (entry)
{
  setLabelName(entry);

  // label initialization
  _label = std::make_shared<sf::Text> ();

  /// \todo better calculus, ratio dependent, eventually, text length dependent
  const auto props(Status::battle()->map()->graphicsProperties());
  _label->setCharacterSize((props->cellWidth() + props->cellHeight()) / 4);

  /// \todo set font and label using a DB
  _font = resources::ResourcesManager::getFont("font_army");
  _label->setFont(*(_font.getFont()));
  _label->setString(_labelName);
}


void MenuEntry::update(const std::shared_ptr<Map::MapGraphicsProperties> properties)
{
  auto width(properties->cellWidth());
  auto height(properties->cellHeight());

  _image.setSize(width * 2, height);
  _label->setPosition(_position.x, _position.y);
  _image.sprite()->setPosition(_position.x, _position.y);
}


void MenuEntry::draw()
{
  PRINTF("drawing", _label->getString().toAnsiString());

  graphics::GraphicsEngine::draw(_label);
  graphics::GraphicsEngine::draw(_image.sprite());
}



void MenuEntry::execute()
{
  PRINTF("executing", (int) _id);
  _callback();
  return;
}



void MenuEntry::setLabelName(e_entry entry)
{
  switch (entry)
  {
    case e_entry::MOVE:
      _labelName = "Move";
      // _callback = // {map ? player ? unit ?}->moveUnit
      // unit: use FoV, movement, inventory, ...
      break;
    case e_entry::WAIT:
      _labelName = "Wait";
      break;
    case e_entry::NEXT_TURN:
      _labelName = "Next Turn";
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
      assert(false);
      break;
  }
}


} // namespace interface
