#include <context/StateGlobal.hh>

#include <debug/Debug.hh>
#include <common/enums/input.hh>
#include <input/EventManager.hh>
#include <graphics/GraphicsEngine.hh>
#include <game/Status.hh>
#include <game/Player.hh>




StateGlobal::StateGlobal()
  : State()
{
  _evtMgr->registerEvent(e_input::SCREENSHOT,   [=] { screenshot(); });

  _evtMgr->registerEvent(e_input::TOGGLE_PANEL,
                         [=] { game::Status::player()->togglePanel(); });
}


void StateGlobal::screenshot()
{
  graphics::GraphicsEngine::screenshotRequest();
}
