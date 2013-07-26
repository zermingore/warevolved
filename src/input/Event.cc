#include <input/Event.hh>
#include <common/Status.hh>
#include <common/globals.hh>
#include <interface/Interface.hh>


Event::Event(KeyManager *km, GraphicEngine *ge) :
  _km(km),
  _ge(ge)
{
  for (unsigned int i = 0; i < E_TIMER_NB_TIMERS; ++i)
    _km->restartTimer(static_cast<e_timer>(i));

  g_settings->setKeyRepeatDelay(150);
  _inGameMenu = g_interface->getInGameMenu();
  _path = g_interface->getPath();
}

Event::~Event() {
}

bool Event::process()
{
  while (WINDOW->pollEvent(_event))
  {
    // Close window : exit request
    if (_event.type == sf::Event::Closed)
    {
      WINDOW->close();
      return false;
    }
  }
  if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) &&
      (_km->getSwitchStatus(E_SWITCH_EXIT) == OFF))
  {
    g_status->exitCurrentMode();
    _inGameMenu->resetSelectedEntry();
    _km->setSwitchStatus(E_SWITCH_EXIT, ON);
  }

  if (_event.type == sf::Event::KeyReleased)
    this->releasedKeys();

  this->panel();

  switch (CURRENT_MODE)
  {
    case E_MODE_SELECTION_MENU:
      if (_path)
        _path->clearPath();

      this->selectionEntriesMenu(_inGameMenu);
      break;

    case E_MODE_ACTION_MENU:
      //_path->shadowPath(); // TODO
      this->selectionEntriesMenu(_inGameMenu);
      break;

    case E_MODE_MOVING_UNIT:
      this->moveUnit();
      break;

    case E_MODE_NONE: // empty mode stack
      WINDOW->close();
      return false;

    default:
      this->game();
      break;
  }

  return true;
}

void Event::panel() {
}

void Event::moveUnit() // only called on E_MODE_MOVING_UNIT
{
  // ---------- Selection ---------- //
  if (_km->selection() && _km->getSwitchStatus(E_SWITCH_SELECTION) == OFF)
  {
    g_status->pushModeInGameMenu(E_MODE_ACTION_MENU, _inGameMenu);
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


void Event::selectionEntriesMenu(EntriesMenu *menu)
{
  // made a choice in selection menu
  if (_km->selection() && _km->getSwitchStatus(E_SWITCH_SELECTION) == OFF)
  {
    menu->executeEntry();
    _km->setSwitchStatus(E_SWITCH_SELECTION, ON);
    return;
  }

  if (_km->up() && _km->ready(E_TIMER_MOVE_UP))
  {
    menu->incrementSelectedEntry();
    _km->setReady(E_TIMER_MOVE_UP, false);
  }

  if (_km->down() && _km->ready(E_TIMER_MOVE_DOWN))
  {
    menu->decrementSelectedEntry();
    _km->setReady(E_TIMER_MOVE_DOWN, false);
  }
}


void Event::game()
{
  // opened selection menu
  if (_km->selection() && _km->getSwitchStatus(E_SWITCH_SELECTION) == OFF)
  {
    g_status->cellSelection();
    _km->setSwitchStatus(E_SWITCH_SELECTION, ON);

    if (CURRENT_MODE == E_MODE_ACTION_MENU)
    {
      DEBUG_PRINT("exec");
      g_status->exitCurrentMode();
      return;
    }

    if (CURRENT_MODE == E_MODE_MOVING_UNIT)
    {
      g_status->pushModeInGameMenu(E_MODE_ACTION_MENU, _inGameMenu);
      return;
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

  if (!_km->selection() && _km->getSwitchStatus(E_SWITCH_SELECTION) == ON)
    _km->setSwitchStatus(E_SWITCH_SELECTION, OFF);

  if (!_km->exit())
    _km->setSwitchStatus(E_SWITCH_EXIT, OFF);
}
