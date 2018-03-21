/**
 * \file
 * \date November 25, 2016
 * \author Zermingore
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
   * \param texture Terrain's associated texture
   */
  Terrain(int cover, const std::string& texture_name);


  /**
   * \brief Defense value getter
   */
  const auto cover() const { return _cover; }

  /**
   * \brief Texture getter
   */
  const auto texture() const { return _texture; }

  /**
   * \brief Identifier getter as a string
   * \return The Texture name
   * \note Used in the Panel to print the Terrain name or retrieve its texture
   */
  const std::string& name() const;



private:
  int _cover; ///< Protection value
  const std::string _textureName; ///< Texture name, also used as an id
  std::shared_ptr<graphics::Texture> _texture; ///< Graphical image
};


#endif /* !TERRAIN_HH_ */
