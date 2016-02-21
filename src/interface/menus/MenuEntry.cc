#include <interface/menus/MenuEntry.hh>
#include <resources/ResourcesManager.hh>
#include <common/Status.hh>


MenuEntry::MenuEntry(entry &entry) :
  _id (entry),
  _background ("selection_menu_button"),
  _labelName ("LABEL UNSET") // could use a #ifdef debug
{
  PRINTF("NOT yet implemented MenuEntry Ctor");

  // _background = GETIMAGE("selection_menu_button");
  // _background.setSize(Coords(2 * CELL_WIDTH, CELL_HEIGHT));

   /// \todo set font and label using a DB
}


MenuEntry::MenuEntry(std::string label_name, entry entry)
{
  // _background = GETIMAGE("selection_menu_button");
  // _background.setSize(Coords(2 * CELL_WIDTH, CELL_HEIGHT));

  // label initialization
   /// \todo better calculus, ratio dependent, eventually, text length dependent
  // _label = std::make_shared<sf::Text> ();
  // _label->setCharacterSize((CELL_WIDTH + CELL_HEIGHT) / 4);

  // // _font = resources::ResourcesManager::getFont("font_army");
  // _label->setFont(*(_font.getFont()));
  // _label->setString(label_name);

  _labelName = label_name;
  _id = entry;
}


void MenuEntry::draw(Coords position)
{
  // _background.setPosition(position);
  // _label->setPosition(position);

  // _background.draw();
  // g_window->draw(*_label);
}


void MenuEntry::execute()
{
  switch (_id)
  {
  //   case entry::ATTACK:
  //   {
  //     g_status->pushMode(E_MODE_ATTACK);
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

  //     g_status->exitToMode(E_MODE_PLAYING, true);
  //     g_interface->path()->hideAllowedPath();
  //     break;
  //   }

  //   case entry::MOVE:
  //   {
  //     g_status->pushMode(E_MODE_MOVING_UNIT);
  //     g_status->setSelectedUnitPosition(CURSOR->coords());
  //     g_interface->setPathOrigin(CURSOR->coords());
  //     break;
  //   }

  //   case entry::NEXT_TURN:
  //     BATTLE->nextPlayer();
  //     g_status->exitCurrentMode(true);
  //     break;

  //   case entry::CANCEL:
  //   {
  //     auto old_mode (CURRENT_MODE);
  //     g_interface->inGameMenu()->loadMenu();

  //     // if we were dealing with orders, return to the unit position
  //     if (old_mode == E_MODE_ACTION_MENU && CURRENT_MODE == E_MODE_MOVING_UNIT)
  //     {
  //       g_status->exitCurrentMode();
  //       // re-build menu at selection state
  //       g_interface->inGameMenu()->build(CURRENT_MODE);
  //     }
  //     break;
  //   }

    default:
      Debug::logPrintf("unable to match selection menu entry");
      break;
  }
}
