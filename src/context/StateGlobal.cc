#include <context/StateGlobal.hh>

#include <debug/Debug.hh>
#include <common/enums/input.hh>
#include <input/EventManager.hh>
#include <graphics/GraphicsEngine.hh>
#include <game/Status.hh>
#include <game/Player.hh>
#include <game/Map.hh>
#include <game/Battle.hh>



StateGlobal::StateGlobal()
  : State()
{
  _evtMgr->registerEvent(e_input::SCREENSHOT, [=] { screenshot(); });
  _evtMgr->registerEvent(e_input::DUMP_MAP,   [=] { dumpMap(); });
  _evtMgr->registerEvent(e_input::QUICK_SAVE, [=] { quickSave(); });
  _evtMgr->registerEvent(e_input::QUICK_LOAD, [=] { quickLoad(); });

  _evtMgr->registerEvent(e_input::TOGGLE_PANEL,
                         [=] { game::Status::player()->togglePanel(); });
}



void StateGlobal::screenshot()
{
  graphics::GraphicsEngine::screenshotRequest();
}



void StateGlobal::dumpMap()
{
  game::Status::battle()->map()->dump();
}


void StateGlobal::quickSave()
{
  game::Status::battle()->saveMap();
}

void StateGlobal::quickLoad()
{
  ERROR("quickLoad not implemented yet"); /// \todo
}
