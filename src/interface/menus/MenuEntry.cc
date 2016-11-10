#include <interface/menus/MenuEntry.hh>
#include <resources/ResourcesManager.hh>
#include <common/Status.hh>
#include <game/applications/Battle.hh>
#include <game/Player.hh>
#include <graphics/GraphicsEngine.hh>



namespace interface {


MenuEntry::MenuEntry(e_entry entry)
  : InterfaceElement("selection_menu_button")
  , _id (entry)
{
  _labelName = "UNSET";

  // _background.setSize(Coords(2 * CELL_WIDTH, CELL_HEIGHT));

  // label initialization
  /// \todo better calculus, ratio dependent, eventually, text length dependent
  _label = std::make_shared<sf::Text> ();

  const auto props(Status::battle()->map()->graphicsProperties());
  _label->setCharacterSize((props->cellWidth() + props->cellHeight()) / 4);

  /// \todo set font and label using a DB
  _font = resources::ResourcesManager::getFont("font_army");
  _label->setFont(*(_font.getFont()));
  _label->setString(_labelName);
}



void MenuEntry::update(const std::shared_ptr<Map::MapGraphicsProperties> properties)
{
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

  //   case entry::MOVE:
  //   {
  //     g_status->pushState(E_STATE_MOVING_UNIT);
  //     g_status->setSelectedUnitPosition(CURSOR->coords());
  //     g_interface->setPathOrigin(CURSOR->coords());
  //     break;
  //   }

  //   case entry::NEXT_TURN:
  //     BATTLE->nextPlayer();
  //     g_status->exitCurrentState(true);
  //     break;

  //   case entry::CANCEL:
  //   {
  //     auto old_state (CURRENT_STATE);
  //     g_interface->inGameMenu()->loadMenu();

  //     // if we were dealing with orders, return to the unit position
  //     if (old_state == E_STATE_ACTION_MENU && CURRENT_STATE == E_STATE_MOVING_UNIT)
  //     {
  //       g_status->exitCurrentState();
  //       // re-build menu at selection state
  //       g_interface->inGameMenu()->build(CURRENT_STATE);
  //     }
  //     break;
  //   }

    default:
      Debug::logPrintf("unable to match selection menu entry");
      break;
  }
}


} // namespace interface
