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
enum class e_unit;


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
   * \brief Get a Terrain given its id
   * \param id Terrain identifier
   * \return Terrain of the list matching the given id
   */
  static const Terrain& get(e_terrain id);

  /**
   * \brief Get the cost to cross a terrain
   * \param terrain Type of the Terrain to cross
   * \param unit_type Type of the Unit willing to cross
   * \return Motion cost (negative value if crossing the terrain is not allowed)
   */
  static size_t cost(const e_terrain terrain, const e_unit unit_type);


private:
  // not const: Terrain needs the ResourcesManager (static) initialization
  /// Mapping Terrain identifier -> Terrain
  static std::map<e_terrain, const Terrain> _terrains;
};


#endif /* !TERRAINS_HANDLER_HH_ */
