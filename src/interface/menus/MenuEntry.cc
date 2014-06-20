#include <interface/menus/MenuEntry.hh>
#include <common/include.hh>
#include <common/globals.hh>
#include <common/Status.hh>
#include <common/macros.hh>


MenuEntry::MenuEntry(e_entry &entry) :
  _id (entry)
{
  DEBUG_PRINT("NOT yet implemented MenuEntry Ctor");

  _background = GETIMAGE("selection_menu_button");
  _background.setSize(sf::Vector2f(2 * CELL_WIDTH, CELL_HEIGHT));

  // TODO set font and label using a DB
}


MenuEntry::MenuEntry(std::string label_name, e_entry entry)
{
  _background = GETIMAGE("selection_menu_button");
  _background.setSize(sf::Vector2f(2 * CELL_WIDTH, CELL_HEIGHT));

  // label initialization
  // TODO better calculus, ratio dependent, eventually, text length dependent
  _label.reset(new sf::Text());
  _label->setCharacterSize((CELL_WIDTH + CELL_HEIGHT) / 4);

  _font = g_rm->getFont("font_army");
  _label->setFont(*(_font.getFont()));
  _label->setString(label_name);

  _id = entry;
}

void MenuEntry::draw(sf::Vector2f position)
{
  _background.setPosition(position);
  _label->setPosition(position);

  _background.draw();
  g_window->draw(*_label);
}


void MenuEntry::execute()
{
  switch (_id)
  {
    case E_ENTRY_ATTACK:
      PRINTF("attack");
      break;

    case E_ENTRY_STOP:
    {
      auto selectedUnit(MAP.unit(g_status->selectedUnitPosition()));
      selectedUnit->setLocation(CURSOR->coords());
      if (g_status->selectedUnitPosition() != CURSOR->coords())
        MAP.moveUnit();

      g_status->exitToMode(E_MODE_PLAYING, true);
      g_interface->path()->hideAllowedPath();
      break;
    }

    case E_ENTRY_MOVE:
    {
      g_status->pushMode(E_MODE_MOVING_UNIT);
      g_status->setSelectedUnitPosition(CURSOR->coords());
      g_interface->setPathOrigin(CURSOR->coords());
      break;
    }

    case E_ENTRY_NEXT_TURN:
      BATTLE->nextPlayer();
      g_status->exitCurrentMode(true);
      break;

    case E_ENTRY_CANCEL:
    {
      auto old_mode(CURRENT_MODE);
      g_interface->inGameMenu()->loadMenu();

      // if we were dealing with orders, return to the unit position
      if (old_mode == E_MODE_ACTION_MENU && CURRENT_MODE == E_MODE_MOVING_UNIT)
      {
        g_status->exitCurrentMode();
        // re-build menu at selection state
        g_interface->inGameMenu()->build(CURRENT_MODE);
      }
      break;
    }

    default:
      Debug::logPrintf("unable to match selection menu entry");
      break;
  }
}
