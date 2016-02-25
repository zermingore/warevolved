#include <input/EventManager.hh>
#include <common/enums/modes.hh>
#include <input/KeyManager.hh>
#include <common/Status.hh>
#include <common/Settings.hh>
#include <interface/Interface.hh>
#include <graphics/GraphicsEngine.hh>


EventManager::EventManager()
{
  _km = std::make_shared<KeyManager> ();
  for (auto i = 0; i < E_TIMER_NB_TIMERS; ++i)
    _km->restartTimer(static_cast<e_timer> (i));

  Settings::setKeyRepeatDelay(150);
}


bool EventManager::execute(std::string key)
{
  if (_callbacks.find(key) == _callbacks.end())
  {
    Debug::printf("callback not found");
    return false;
  }

  _callbacks[key]();
  return true;
}


bool EventManager::process()
{
  while (graphics::GraphicsEngine::pollEvent(_event))
  {
    // Close window : exit request
    if (_event.type == sf::Event::Closed)
    {
      graphics::GraphicsEngine::closeWindow();
      return false;
    }
  }

  if (_event.type == sf::Event::KeyReleased)
    releasedKeys();

  panels(); // in all mode, for now
  switch (Status::currentMode())
  {
    case e_mode::SELECTION_MENU:
      // Interface::path()->clearPath();

      selectionMenu();
      break;

    case e_mode::ACTION_MENU:
      //_path->shadowPath();  /// \todo less visible path
      selectionMenu();
      break;

    case e_mode::MOVING_UNIT:
      // moveUnit();
      break;

    case e_mode::ATTACK:
      // selectTarget();
      break;

    case e_mode::NONE: // mode stack is empty
      graphics::GraphicsEngine::closeWindow();
      return false;

    default:
      return game();
  }

  return true;
}



void EventManager::panels()
{
  // if (_km->panel() && _km->switchStatus(E_SWITCH_PANEL) == OFF)
  // {
  //   g_interface->incrementPanelPosition();
  //   _km->setSwitchStatus(E_SWITCH_PANEL, ON);
  //   return;
  // }

  // if (_km->menubar() && _km->switchStatus(E_SWITCH_MENUBAR) == OFF)
  // {
  //   g_interface->incrementMenuBarPosition();
  //   _km->setSwitchStatus(E_SWITCH_MENUBAR, ON);
  //   return;
  // }
}


void EventManager::selectTarget()
{
  // quit mode request
  if (_km->exit() && _km->switchStatus(E_SWITCH_EXIT) == OFF)
  {
    Status::exitCurrentMode();
//    _inGameMenu->build(CURRENT_MODE); // re-build menu
    _km->setSwitchStatus(E_SWITCH_EXIT, ON);
    return;
  }

  // auto selectedUnit (_path->unit());

  // // browsing targets
  // if ((_km->down() && _km->ready(E_TIMER_MOVE_DOWN)) ||
  //     (_km->left() && _km->ready(E_TIMER_MOVE_LEFT)))
  // {
  //   auto prev = selectedUnit->previousTarget();
  //   Status::setCursorCoords(Coords(prev->x(), prev->y()));
  //   _km->setReady(E_TIMER_MOVE_DOWN, false);
  //   _km->setReady(E_TIMER_MOVE_LEFT, false);
  // }
  // if ((_km->up() && _km->ready(E_TIMER_MOVE_UP)) ||
  //     (_km->right() && _km->ready(E_TIMER_MOVE_RIGHT)))
  // {
  //   auto next = selectedUnit->nextTarget();
  //   Status::setCursorCoords(Coords(next->x(), next->y()));
  //   _km->setReady(E_TIMER_MOVE_UP, false);
  //   _km->setReady(E_TIMER_MOVE_RIGHT, false);
  // }

  // if (_km->selection() && _km->switchStatus(E_SWITCH_SELECTION) == OFF)
  // {
  //   _km->setSwitchStatus(E_SWITCH_SELECTION, ON);
  //   if (selectedUnit->attack() == false) // unit died in fight
  //   {
  //     _path->removeUnit();
  //     selectedUnit.reset();
  //   }
  //   else // the unit survived, move it if needed
  //   {
  //     if (selectedUnit->coords() != selectedUnit->attackCoords())
  //       MAP.moveUnit(selectedUnit, selectedUnit->attackCoords());
  //     selectedUnit->setPlayed(true);
  //   }

  //   Status::exitToMode(mode::PLAYING, true);
  //   g_interface->path()->hideAllowedPath();
  // }
}


void EventManager::moveUnit()
{
  // only called on mode::MOVING_UNIT
  assert(Status::currentMode() != e_mode::MOVING_UNIT);
  if (_km->exit() && _km->switchStatus(E_SWITCH_EXIT) == OFF)
  {
    Status::exitCurrentMode();
    // _inGameMenu->build(CURRENT_MODE); // re-build menu at selection state
    _km->setSwitchStatus(E_SWITCH_EXIT, ON);

    return;
  }

  // // ---------- Selection ---------- //
  // if (_km->selection() && _km->switchStatus(E_SWITCH_SELECTION) == OFF)
  // {
  //   Status::pushModeInGameMenu(mode::ACTION_MENU, _inGameMenu);
  //   _km->setSwitchStatus(E_SWITCH_SELECTION, ON);
  //   return;
  // }

  // // ---------- Motion ---------- //
  // if (!_path->allowedMove())
  //   return;

  // if (_km->up() && _km->ready(E_TIMER_MOVE_UP))
  // {
  //   if (CURSOR->moveUp())
  //     _path->addNextDirection(E_DIRECTION_UP);

  //   // the timer will not be ready until
  //   //   key_repeat_delay passed OR we release the key pressed
  //   _km->setReady(E_TIMER_MOVE_UP, false);
  // }

  // if (_km->down() && _km->ready(E_TIMER_MOVE_DOWN))
  // {
  //   if (CURSOR->moveDown())
  //     _path->addNextDirection(E_DIRECTION_DOWN);
  //   _km->setReady(E_TIMER_MOVE_DOWN, false);
  // }

  // if (_km->left() && _km->ready(E_TIMER_MOVE_LEFT))
  // {
  //   if (CURSOR->moveLeft())
  //     _path->addNextDirection(E_DIRECTION_LEFT);
  //   _km->setReady(E_TIMER_MOVE_LEFT, false);
  // }

  // if (_km->right() && _km->ready(E_TIMER_MOVE_RIGHT))
  // {
  //   if (CURSOR->moveRight())
  //     _path->addNextDirection(E_DIRECTION_RIGHT);
  //   _km->setReady(E_TIMER_MOVE_RIGHT, false);
  // }
}


void EventManager::selectionMenu()
{
  // if (_km->exit() && _km->switchStatus(E_SWITCH_EXIT) == OFF)
  // {
  //   e_mode old_mode = Status::currentMode();
  //   _inGameMenu->resetSelectedEntry();
  //   _inGameMenu->loadMenu();

  //   // we were dealing with orders, return to the unit position
  //   if (old_mode == mode::ACTION_MENU && CURRENT_MODE == mode::MOVING_UNIT)
  //   {
  //     Status::exitCurrentMode();
  //     _inGameMenu->build(CURRENT_MODE); // re-build menu at selection state
  //   }
  //   _km->setSwitchStatus(E_SWITCH_EXIT, ON);

  //   return; // we just quit this mode
  // }

  // // made a choice in selection menu
  // if (_km->selection() && _km->switchStatus(E_SWITCH_SELECTION) == OFF)
  // {
  //   _inGameMenu->executeEntry();
  //   _km->setSwitchStatus(E_SWITCH_SELECTION, ON);
  //   return;
  // }
  // if (_km->up() && _km->ready(E_TIMER_MOVE_UP))
  // {
  //   _inGameMenu->incrementSelectedEntry();
  //   _km->setReady(E_TIMER_MOVE_UP, false);
  // }

  // if (_km->down() && _km->ready(E_TIMER_MOVE_DOWN))
  // {
  //   _inGameMenu->decrementSelectedEntry();
  //   _km->setReady(E_TIMER_MOVE_DOWN, false);
  // }
}


bool EventManager::game()
{
  if (_km->exit() && _km->switchStatus(E_SWITCH_EXIT) == OFF)
  {
    Status::exitCurrentMode();
    _km->setSwitchStatus(E_SWITCH_EXIT, ON);
    graphics::GraphicsEngine::closeWindow();

    return false;
  }

  if (_km->menubar() && _km->switchStatus(E_SWITCH_MENUBAR) == OFF)
    _km->setSwitchStatus(E_SWITCH_MENUBAR, ON);

  // opened selection menu
  // if (_km->selection() && _km->switchStatus(E_SWITCH_SELECTION) == OFF)
  // {
  //   Status::cellSelection();
  //   _km->setSwitchStatus(E_SWITCH_SELECTION, ON);

  //   if (CURRENT_MODE == mode::ACTION_MENU)
  //   {
  //     Status::exitCurrentMode();
  //     return true;
  //   }

  //   if (CURRENT_MODE == mode::MOVING_UNIT)
  //   {
  //     Status::pushModeInGameMenu(mode::ACTION_MENU, _inGameMenu);
  //     return true;
  //   }

  //   _path->clearPath();
  //   Status::pushModeInGameMenu(mode::SELECTION_MENU, _inGameMenu);
  // }

  // // ---------- Cursor Motion ---------- //
  // if (_km->up() && _km->ready(E_TIMER_MOVE_UP))
  // {
  //   CURSOR->moveUp();
  //   // the timer will not be ready until
  //   //   key_repeat_delay passed OR we release the key pressed
  //   _km->setReady(E_TIMER_MOVE_UP, false);
  // }

  // if (_km->down() && _km->ready(E_TIMER_MOVE_DOWN))
  // {
  //   CURSOR->moveDown();
  //   _km->setReady(E_TIMER_MOVE_DOWN, false);
  // }

  // if (_km->left() && _km->ready(E_TIMER_MOVE_LEFT))
  // {
  //   CURSOR->moveLeft();
  //   _km->setReady(E_TIMER_MOVE_LEFT, false);
  // }

  // if (_km->right() && _km->ready(E_TIMER_MOVE_RIGHT))
  // {
  //   CURSOR->moveRight();
  //   _km->setReady(E_TIMER_MOVE_RIGHT, false);
  // }

  return true;
}


void EventManager::releasedKeys()
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
