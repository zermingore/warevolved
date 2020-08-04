/**
 * \file
 * \date September 19, 2017
 * \author Zermingore
 * \brief TerrainsHandler class declaration
 */

#ifndef TERRAINS_HANDLER_HH_
# define TERRAINS_HANDLER_HH_

# include <map>

class Terrain;
enum class e_terrain;



/**
 * \class TerrainsHandler
 * \brief Class handling a list of Terrains
 */
class TerrainsHandler
{
public:
  /**
   * \brief Initializes the exhaustive terrains list
   *   with their respective Textures
   */
  static void initialize();

  /**
   * \brief Return the Terrain of the list matching the given id
   * \param id Terrain identifier
   */
  static const Terrain& get(e_terrain id);


private:
  /// Mapping Terrain identifier -> Terrain
  static std::map<e_terrain, const Terrain> _terrains;
};


#endif /* !TERRAINS_HANDLER_HH_ */
