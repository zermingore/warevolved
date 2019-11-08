#include <context/StateGlobal.hh>

#include <lib/pugixml.hh>

#include <common/enums/input.hh>
#include <debug/Debug.hh>
#include <game/Battle.hh>
#include <game/Map.hh>
#include <game/Player.hh>
#include <game/Status.hh>
#include <graphics/GraphicsEngine.hh>
#include <input/EventManager.hh>



StateGlobal::StateGlobal()
{
  _evtMgr->registerEvent(e_input::SCREENSHOT, [&] { screenshot(); });
  _evtMgr->registerEvent(e_input::DUMP_MAP,   [&] { dumpMap();    });
  _evtMgr->registerEvent(e_input::QUICK_SAVE, [&] { quickSave();  });
  _evtMgr->registerEvent(e_input::QUICK_LOAD, [&] { quickLoad();  });

  _evtMgr->registerEvent(e_input::TOGGLE_PANEL,
                         [&] { game::Status::player()->togglePanel(); });
}



void StateGlobal::screenshot()
{
  graphics::GraphicsEngine::screenshotRequest();
}



void StateGlobal::dumpMap()
{
  auto doc{game::Status::battle()->map()->dump()};
  doc->print(std::cout);
}



void StateGlobal::quickSave()
{
  game::Status::battle()->saveMap();
}



void StateGlobal::quickLoad()
{
  ERROR("quickLoad not implemented yet"); /// \todo implement
}
