/**
 * \file
 * \date September 19, 2017
 * \author Zermingore
 * \brief TerrainsHandler class declaration
 */


#ifndef TERRAINS_HANDLER_HH_
# define TERRAINS_HANDLER_HH_

# include <map>
# include <memory>
# include <common/enums/terrains.hh>

class Terrain;


/**
 * \class TerrainsHandler
 * \brief Class handling a list of Terrains
 */
class TerrainsHandler
{
public:
  /**
   * \brief Initializes the possible terrains
   */
  TerrainsHandler();

  /**
   * \brief Return the Terrain of the list matching the given id
   */
  std::shared_ptr<const Terrain> getTerrain(e_terrain id);

private:
  std::map<e_terrain, std::shared_ptr<Terrain>> _terrains;
};

#endif /* !TERRAINS_HANDLER_HH_ */
