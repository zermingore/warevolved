/**
 * \file
 * \date July 29, 2020
 * \author Zermingore
 * \brief Random class definition
 */

#include <tools/Random.hh>
#include <tools/options/OptionsParser.hh>
#include <game/Cell.hh>
#include <game/Terrain.hh>
#include <debug/Debug.hh>


long unsigned int Random::_randomSeed;
std::unique_ptr<std::mt19937> Random::_generator;



void Random::init(const OptionsParser& options_parser)
{
  // Extract the random seed, if provided
  if (options_parser.optionExists("random-seed"))
  {
    _randomSeed =
      std::stoul(options_parser["random-seed"].value().arguments()[0]);
  }

# pragma GCC diagnostic push // random_device and mt19937 are 5k on my machine
# pragma GCC diagnostic ignored "-Wlarger-than="
  std::random_device rd;
  if (_randomSeed == 0u)
  {
    _randomSeed = rd();
  }
  NOTICE("Using random seed:", _randomSeed);
  _generator = std::make_unique<std::mt19937> (_randomSeed);
# pragma GCC diagnostic pop
}



int Random::randInt(int min, int max)
{
  std::uniform_int_distribution<> rand(min, max);
  return rand(*_generator);
}


e_terrain Random::randTerrain()
{
  std::uniform_int_distribution<> rand(
    1, static_cast<int> (e_terrain::NB_TERRAIN) -1);

  // Avoid buildings
  auto ret{static_cast<e_terrain> (rand(*_generator))};
  if (   ret == e_terrain::BUILDING_DOOR
      || ret == e_terrain::BUILDING_WINDOW
      || ret == e_terrain::BUILDING_WINDOW_FIRST)
  {
    ret = e_terrain::PLAIN;
  }
  else if (   ret == e_terrain::BUILDING_LAST_STAGE
           || ret == e_terrain::BUILDING_ROOF)
  {
    ret = e_terrain::FOREST;
  }

  return ret;
}


bool Random::randBool()
{
  std::uniform_int_distribution<> rand(0, 1);
  return rand(*_generator);
}
