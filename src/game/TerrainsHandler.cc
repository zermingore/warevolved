#include <game/TerrainsHandler.hh>

#include <game/Terrain.hh>
#include <graphics/graphic_types.hh>
#include <resources/ResourcesManager.hh>



TerrainsHandler::TerrainsHandler()
{
  using namespace resources; // for the ResourcesManager

  /// \todo Find a way to do a for-range on the e_terrain enum
  _terrains[e_terrain::FOREST] =
    std::make_shared<Terrain> (1, ResourcesManager::getTexture("forest"));
}



std::shared_ptr<Terrain> TerrainsHandler::getTerrain(e_terrain id)
{
  return _terrains[id]; /// \todo error handling
}
