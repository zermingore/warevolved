/**
 * \file
 * \date September 19, 2017
 * \author Zermingore
 * \brief TerrainsHandler class definition
 */

#include <game/TerrainsHandler.hh>

#include <debug/Debug.hh>
#include <game/Terrain.hh>
#include <game/units/Unit.hh>
#include <graphics/graphic_types.hh>


std::map<e_terrain, const Terrain> TerrainsHandler::_terrains;


void TerrainsHandler::initialize()
{
  TerrainsHandler::_terrains = {
    { e_terrain::PLAIN,  {1, "plain" } },
    { e_terrain::FOREST, {3, "forest"} }
  };
}


size_t TerrainsHandler::cost(const e_terrain terrain, const e_unit unit_type)
{
  switch (terrain)
  {
    case e_terrain::PLAIN:
      return 1;

    case e_terrain::FOREST:
    {
      if (unit_type == e_unit::CAR)
      {
        return 3;
      }
      return 1;
    }

    default:
      ERROR("[cost] Terrain not found", debug::e_terrain_string(terrain));
      return 1000;
  }
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
