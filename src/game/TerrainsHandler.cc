/**
 * \file
 * \date September 19, 2017
 * \author Zermingore
 * \brief TerrainsHandler class definition
 */

#include <game/TerrainsHandler.hh>

#include <debug/Debug.hh>
#include <game/Terrain.hh>
#include <graphics/graphic_types.hh>


std::map<e_terrain, const Terrain> TerrainsHandler::_terrains;


void TerrainsHandler::initialize()
{
  TerrainsHandler::_terrains = {
    { e_terrain::PLAIN,  {1, "plain" } },
    { e_terrain::FOREST, {3, "forest"} }
  };
}



const Terrain& TerrainsHandler::get(const e_terrain id)
{
  try
  {
    return TerrainsHandler::_terrains.at(id);
  }
  catch (std::exception& exc)
  {
    ERROR("The terrain", static_cast<int> (id), "is not in the list");
    ERROR(exc.what());
    throw;
  }
}
