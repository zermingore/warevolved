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



void TerrainsHandler::initialize()
{
  TerrainsHandler::_terrains = {
    { e_terrain::PLAIN,  {1, "plain" } },
    { e_terrain::FOREST, {3, "forest"} },

    { e_terrain::BUILDING_DOOR,         {2, "building_door"        } },
    { e_terrain::BUILDING_WINDOW,       {4, "building_window"      } },
    { e_terrain::BUILDING_WINDOW_FIRST, {3, "building_window_first"} },
    { e_terrain::BUILDING_LAST_STAGE,   {5, "building_last_stage"  } },
    { e_terrain::BUILDING_ROOF,         {6, "building_roof"        } },
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

    case e_terrain::BUILDING_DOOR:
    {
      if (unit_type == e_unit::SOLDIER)
      {
        return 1;
      }

      return 1000; // Direct cross forbidden
    }

    case e_terrain::BUILDING_WINDOW:
    case e_terrain::BUILDING_WINDOW_FIRST:
    case e_terrain::BUILDING_LAST_STAGE:
    case e_terrain::BUILDING_ROOF:
    {
      return 1000; // Direct cross forbidden
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
