#include <interface/menus/MenuEntry.hh>
#include <common/Status.hh>
#include <game/applications/Battle.hh>
#include <graphics/GraphicsEngine.hh>


#include <common/enums/states.hh>



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
  graphics::GraphicsEngine::draw(_label);
  graphics::GraphicsEngine::draw(_image.sprite());
}






void MenuEntry::execute()
{
  Debug::printf("executing", (int) _id);
  _callback();
  return;


  // _________________________ dead code ! _________________________

  /// \todo instead of switching, set a lambda at initialization
  switch (_id)
  {
  //   case entry::ATTACK:
  //   {
  //     g_status->pushState(E_STATE_ATTACK);
  //     auto selectedUnit (MAP.unit(g_status->selectedUnitPosition()));
  //     auto targets (selectedUnit->targets());
  //     selectedUnit->setAttackCoords(CURSOR->coords());
  //     CURSOR->setCoords((*targets)[0]->getCoords());
  //     break;
  //   }

  //   case entry::STOP:
  //   {
  //     auto selectedUnit (MAP.unit(g_status->selectedUnitPosition()));
  //     selectedUnit->setCoords(CURSOR->coords());
  //     if (g_status->selectedUnitPosition() != CURSOR->coords())
  //       MAP.moveUnit();

  //     g_status->exitToState(E_STATE_PLAYING, true);
  //     g_interface->path()->hideAllowedPath();
  //     break;
  //   }

    case e_entry::MOVE:
    {
      Debug::printf("_________________________MOVE");
      // g_status->pushState(E_STATE_MOVING_UNIT);
      // g_status->setSelectedUnitPosition(CURSOR->coords());
      // g_interface->setPathOrigin(CURSOR->coords());
      break;
    }

  //   case entry::NEXT_TURN:
  //     BATTLE->nextPlayer();
  //     g_status->exitCurrentState(true);
  //     break;


    default:
      Debug::logPrintf("unable to match selection menu entry");
      break;
  }
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
    case e_entry::STOP:
      _labelName = "Stop";
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
      Debug::error("No label found for e_entry", static_cast<int> (entry));
      break;
  }
}


} // namespace interface
