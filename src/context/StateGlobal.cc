#include <context/StateGlobal.hh>

#include <lib/pugixml.hh>

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
  _evtMgr->registerEvent(e_input::SCREENSHOT, [=, this] { screenshot(); });
  _evtMgr->registerEvent(e_input::DUMP_MAP,   [=, this] { dumpMap(); });
  _evtMgr->registerEvent(e_input::QUICK_SAVE, [=, this] { quickSave(); });
  _evtMgr->registerEvent(e_input::QUICK_LOAD, [=, this] { quickLoad(); });

  _evtMgr->registerEvent(e_input::TOGGLE_PANEL,
                         [=, this] { game::Status::player()->togglePanel(); });
}



void StateGlobal::screenshot()
{
  graphics::GraphicsEngine::screenshotRequest();
}



void StateGlobal::dumpMap()
{
  pugi::xml_document doc;
  game::Status::battle()->map()->dump(doc);
  doc.print(std::cout);
}


void StateGlobal::quickSave()
{
  game::Status::battle()->saveMap();
}

void StateGlobal::quickLoad()
{
  ERROR("quickLoad not implemented yet"); /// \todo implement
}
