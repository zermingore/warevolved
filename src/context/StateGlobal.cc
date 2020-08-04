/**
 * \file
 * \date July 27, 2017
 * \author Zermingore
 * \brief StateGlobal class definition
 */

#include <context/StateGlobal.hh>

#include <lib/pugixml.hh>

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



void StateGlobal::screenshot() const
{
  graphics::GraphicsEngine::screenshotRequest();
}



void StateGlobal::dumpMap() const
{
  const auto doc{game::Status::battle()->map()->dump()};
  doc->print(std::cout);
}



void StateGlobal::quickSave() const
{
  game::Status::battle()->saveMap();
}



void StateGlobal::quickLoad() const
{
  ERROR("quickLoad not implemented yet"); /// \todo implement
}
