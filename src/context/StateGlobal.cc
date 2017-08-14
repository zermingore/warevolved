#include <context/StateGlobal.hh>

#include <debug/Debug.hh>
#include <common/enums/input.hh>
#include <input/EventManager.hh>
#include <graphics/GraphicsEngine.hh>



StateGlobal::StateGlobal()
  : State()
{
  _evtMgr->registerEvent(e_input::SCREENSHOT,  [=] { screenshot(); });
}


void StateGlobal::screenshot()
{
  NOTICE("SCREENSHOT");
  graphics::GraphicsEngine::screenshot();
}
