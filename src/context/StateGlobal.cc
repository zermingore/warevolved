#include <context/StateGlobal.hh>

#include <debug/Debug.hh>
#include <common/enums/input.hh>
#include <input/EventManager.hh>
#include <graphics/GraphicsEngine.hh>



StateGlobal::StateGlobal()
  : State()
{
  _evtMgr->registerEvent(e_input::SCREENSHOT,   [=] { screenshot(); });
  // _evtMgr->registerEvent(e_input::TOGGLE_PANEL, [=] { togglePanel(); });
}


void StateGlobal::screenshot()
{
  graphics::GraphicsEngine::screenshot();
}
