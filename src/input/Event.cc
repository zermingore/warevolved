#include <input/Event.hh>
#include <common/Status.hh>
#include <common/globals.hh>
#include <interface/Interface.hh>


Event::Event(std::shared_ptr<KeyManager> km, std::shared_ptr<GraphicsEngine> ge) :
  _km(km),
  _ge(ge)
{
  for (auto i = 0; i < E_TIMER_NB_TIMERS; ++i)
    _km->restartTimer(static_cast<e_timer> (i));

  g_settings->setKeyRepeatDelay(150);
  _inGameMenu = g_interface->inGameMenu();
  _path = g_interface->path();
}


bool Event::process()
{
  while (g_window->pollEvent(_event))
  {
    // Close window : exit request
    if (_event.type == sf::Event::Closed)
    {
      g_window->close();
      return false;
    }
  }

  if (_event.type == sf::Event::KeyReleased)
    releasedKeys();

  panels(); // in all mode, for now
  switch (CURRENT_MODE)
  {
    case E_MODE_SELECTION_MENU:
      if (_path)
        _path->clearPath();

      selectionMenu();
      break;

    case E_MODE_ACTION_MENU:
      //_path->shadowPath(); // TODO less visible path
      selectionMenu();
      break;

    case E_MODE_MOVING_UNIT:
      moveUnit();
      break;

    case E_MODE_NONE: // mode stack is empty
      g_window->close();
      return false;

    default:
      return game();
  }

  return true;
}


void Event::panels()
{
  if (_km->panel() && _km->switchStatus(E_SWITCH_PANEL) == OFF)
  {
    g_interface->incrementPanelPosition();
    _km->setSwitchStatus(E_SWITCH_PANEL, ON);
    return;
  }

  if (_km->menubar() && _km->switchStatus(E_SWITCH_MENUBAR) == OFF)
  {
    g_interface->incrementMenuBarPosition();
    _km->setSwitchStatus(E_SWITCH_MENUBAR, ON);
    return;
  }
}


void Event::moveUnit() // only called on E_MODE_MOVING_UNIT
{
  if (_km->exit() && _km->switchStatus(E_SWITCH_EXIT) == OFF)
  {
    g_status->exitCurrentMode();
    _inGameMenu->build(CURRENT_MODE); // re-build menu at selection state
    _km->setSwitchStatus(E_SWITCH_EXIT, ON);

    return;
  }

  // ---------- Selection ---------- //
  if (_km->selection() && _km->switchStatus(E_SWITCH_SELECTION) == OFF)
  {
    g_status->pushModeInGameMenu(E_MODE_ACTION_MENU, _inGameMenu);
    _km->setSwitchStatus(E_SWITCH_SELECTION, ON);
    return;
  }

  // ---------- Motion ---------- //
  if (!_path->allowedMove())
    return;

  if (_km->up() && _km->ready(E_TIMER_MOVE_UP))
  {
    if (CURSOR->moveUp())
      _path->addNextDirection(E_DIRECTION_UP);

    // the timer will not be ready until
    //   key_repeat_delay passed OR we release the key pressed
    _km->setReady(E_TIMER_MOVE_UP, false);
  }

  if (_km->down() && _km->ready(E_TIMER_MOVE_DOWN))
  {
    if (CURSOR->moveDown())
      _path->addNextDirection(E_DIRECTION_DOWN);
    _km->setReady(E_TIMER_MOVE_DOWN, false);
  }

  if (_km->left() && _km->ready(E_TIMER_MOVE_LEFT))
  {
    if (CURSOR->moveLeft())
      _path->addNextDirection(E_DIRECTION_LEFT);
    _km->setReady(E_TIMER_MOVE_LEFT, false);
  }

  if (_km->right() && _km->ready(E_TIMER_MOVE_RIGHT))
  {
    if (CURSOR->moveRight())
      _path->addNextDirection(E_DIRECTION_RIGHT);
    _km->setReady(E_TIMER_MOVE_RIGHT, false);
  }
}


void Event::selectionMenu()
{
  if (_km->exit() && _km->switchStatus(E_SWITCH_EXIT) == OFF)
  {
    e_mode old_mode = CURRENT_MODE;
    _inGameMenu->resetSelectedEntry();
    _inGameMenu->loadMenu();

    // we were dealing with orders, return to the unit position
    if (old_mode == E_MODE_ACTION_MENU && CURRENT_MODE == E_MODE_MOVING_UNIT)
    {
      g_status->exitCurrentMode();
      _inGameMenu->build(CURRENT_MODE); // re-build menu at selection state
    }
    _km->setSwitchStatus(E_SWITCH_EXIT, ON);

    return; // we just quit this mode
  }

  // made a choice in selection menu
  if (_km->selection() && _km->switchStatus(E_SWITCH_SELECTION) == OFF)
  {
    _inGameMenu->executeEntry();
    _km->setSwitchStatus(E_SWITCH_SELECTION, ON);
    return;
  }

  if (_km->up() && _km->ready(E_TIMER_MOVE_UP))
  {
    _inGameMenu->incrementSelectedEntry();
    _km->setReady(E_TIMER_MOVE_UP, false);
  }

  if (_km->down() && _km->ready(E_TIMER_MOVE_DOWN))
  {
    _inGameMenu->decrementSelectedEntry();
    _km->setReady(E_TIMER_MOVE_DOWN, false);
  }
}


bool Event::game()
{
  if (_km->exit() && _km->switchStatus(E_SWITCH_EXIT) == OFF)
  {
    g_status->exitCurrentMode();
    _km->setSwitchStatus(E_SWITCH_EXIT, ON);
    g_window->close();

    return false;
  }

  if (_km->menubar() && _km->switchStatus(E_SWITCH_MENUBAR) == OFF)
    _km->setSwitchStatus(E_SWITCH_MENUBAR, ON);

  // opened selection menu
  if (_km->selection() && _km->switchStatus(E_SWITCH_SELECTION) == OFF)
  {
    g_status->cellSelection();
    _km->setSwitchStatus(E_SWITCH_SELECTION, ON);

    if (CURRENT_MODE == E_MODE_ACTION_MENU)
    {
      PRINTF("exec");
      g_status->exitCurrentMode();
      return true;
    }

    if (CURRENT_MODE == E_MODE_MOVING_UNIT)
    {
      g_status->pushModeInGameMenu(E_MODE_ACTION_MENU, _inGameMenu);
      return true;
    }

    _path->clearPath();
    g_status->pushModeInGameMenu(E_MODE_SELECTION_MENU, _inGameMenu);
  }

  // ---------- Cursor Motion ---------- //
  if (_km->up() && _km->ready(E_TIMER_MOVE_UP))
  {
    CURSOR->moveUp();
    // the timer will not be ready until
    //   key_repeat_delay passed OR we release the key pressed
    _km->setReady(E_TIMER_MOVE_UP, false);
  }

  if (_km->down() && _km->ready(E_TIMER_MOVE_DOWN))
  {
    CURSOR->moveDown();
    _km->setReady(E_TIMER_MOVE_DOWN, false);
  }

  if (_km->left() && _km->ready(E_TIMER_MOVE_LEFT))
  {
    CURSOR->moveLeft();
    _km->setReady(E_TIMER_MOVE_LEFT, false);
  }

  if (_km->right() && _km->ready(E_TIMER_MOVE_RIGHT))
  {
    CURSOR->moveRight();
    _km->setReady(E_TIMER_MOVE_RIGHT, false);
  }

  return true;
}

void Event::releasedKeys()
{
  // The timer we want to reset must not match a pressed key
  // (in case 2 keys are pressed simultaneously)

  if (!_km->up())
    _km->restartTimer(E_TIMER_MOVE_UP);

  if (!_km->down())
    _km->restartTimer(E_TIMER_MOVE_DOWN);

  if (!_km->left())
    _km->restartTimer(E_TIMER_MOVE_LEFT);

  if (!_km->right())
    _km->restartTimer(E_TIMER_MOVE_RIGHT);

  _km->resetSwitches();
}
