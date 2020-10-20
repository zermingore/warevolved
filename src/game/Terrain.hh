/**
 * \file
 * \date November 25, 2016
 * \author Zermingore
 * \brief Terrain class declaration and enum e_terrain definition
 */

#ifndef TERRAIN_HH_
# define TERRAIN_HH_

# include <memory>
# include <graphics/graphic_types.hh>



/**
 * \class Terrain
 * \brief Represents a terrain on a Map Cell
 */
class Terrain
{
public:
  /**
   * \brief Deleted default constructor; attributes required
   */
  Terrain() = delete;

  /**
   * \brief Initializes the terrain with the given defense and texture
   * \param cover How much protection the terrain offers
   * \param texture_name Terrain's associated texture
   */
  Terrain(int cover, const std::string& texture_name);


  /**
   * \brief Defense value getter
   * \return Coverage value
   */
  auto cover() const { return _cover; }

  /**
   * \brief Texture getter
   * \return A pointer on the Texture
   */
  auto texture() const { return _texture; }

  /**
   * \brief Identifier getter as a string
   * \return The Texture name
   * \note Used in the Panel to print the Terrain name or retrieve its texture
   */
  const std::string& name() const { return _textureName; }


private:
  int _cover; ///< Protection value
  const std::string _textureName; ///< Texture name, also used as an id
  std::shared_ptr<graphics::Texture> _texture; ///< Graphical image
};



/**
 * \enum e_terrain
 * \brief Listing of all terrains
 */
enum class e_terrain
{
  NONE = 0,
  PLAIN,
  FOREST,
  BUILDING,
  BUILDING_DOOR,

  NB_TERRAIN
};



#endif /* !TERRAIN_HH_ */
