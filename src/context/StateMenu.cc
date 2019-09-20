#include <context/StateMenu.hh>

#include <debug/Debug.hh>
#include <input/EventManager.hh>
#include <common/enums/input.hh>
#include <common/enums/states.hh>
#include <game/Status.hh>
#include <game/Battle.hh>
#include <game/Player.hh>
#include <game/PathFinding.hh>
#include <interface/menus/Menu.hh>
#include <interface/menus/InGameMenu.hh>
#include <interface/menus/MenuMap.hh>
#include <interface/menus/MenuAction.hh>
#include <interface/menus/MenuCrew.hh>
#include <interface/Cursor.hh>



StateMenu::StateMenu(const e_state state)
  : State()
{
  // browsing entries
  _evtMgr->registerEvent(e_input::MOVE_UP,   [=] { moveUp();   });
  _evtMgr->registerEvent(e_input::MOVE_DOWN, [=] { moveDown(); });

  _evtMgr->registerEvent(e_input::SELECTION, [=] { validate(); });
  _evtMgr->registerEvent(e_input::EXIT,      [=] { exit();     });


  // Building the menu depending on the State
  _menuCoords = game::Status::player()->cursor()->coords();
  switch (state)
  {
    case e_state::MAP_MENU:
      _menu = std::make_shared<interface::MenuMap> ();
      break;

    case e_state::SELECTION_UNIT:
    case e_state::ACTION_MENU:
      _menu = std::make_shared<interface::MenuAction> (state);
      break;

    case e_state::SELECTION_CREW:
      _menu = std::make_shared<interface::MenuCrew> ();
      break;

    default:
      ERROR("StateMenu called with", static_cast<int> (game::Status::state()));
      assert(false && "State is not a menu");
      break;
  }
}


void StateMenu::suspend()
{
  /// \todo set menu at optimal coordinates (avoid hiding units for instance)
  _menuCoords = _menu->coords();
  /// \todo save selected entry
}

void StateMenu::resume()
{
  // retrieve coordinates from the attributes
  if (_attributes.size()) {
    fetchAttributes();
  }

  _menu->setCoords(_menuCoords);
  _menu->build();
}


void StateMenu::moveUp() {
  _menu->moveUp();
}

void StateMenu::moveDown() {
  _menu->moveDown();
}


void StateMenu::validate() {
  _menu->validate();
}


void StateMenu::exit()
{
  game::Status::popCurrentState();
  game::Status::currentState()->resume();
}


void StateMenu::fetchAttributes()
{
  if (!_attributes.size())
  {
    ERROR("StateMenu::fetchAttributes called without available attributes");
    assert(false && "No attribute found");
    return;
  }

  auto p = std::static_pointer_cast<Coords> (_attributes[0]);
  _menuCoords.c = p->c;
  _menuCoords.l = p->l;

  /// \todo fetch selected and hovered units?

  // reset the attributes vector
  _attributes.clear();
}


void StateMenu::draw() {
  _menu->draw();
}
