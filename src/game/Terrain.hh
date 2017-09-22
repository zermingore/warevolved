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
   * \param defense How much cover the terrain offers
   * \param texture Terrain's associated texture
   */
  Terrain(int defense, std::shared_ptr<graphics::Texture> texture);


  /**
   * \brief Texture getter
   */
  auto texture() const { return _texture; }


private:
  int _defense; ///< Defense value
  std::shared_ptr<graphics::Texture> _texture; ///< Graphical image
};


#endif /* !TERRAIN_HH_ */
