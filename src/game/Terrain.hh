#ifndef TERRAIN_HH_
# define TERRAIN_HH_

# include <game/Cell.hh>


# include <resources/ResourcesManager.hh>

/** \brief Terrain
 */

// NOTE we could add a randomized sf::shape
//   (to dodge mosaic sad pattern)

class Terrain
{
public:
  /** \brief Default Constructor
   */
  Terrain();

  Terrain(e_terrains terrain);

  /** \brief Terrain Constructor
   **   builds a Terrain of type terrain
   */
  Terrain(e_terrains terrain, ResourcesManager *rm);


  /** \brief Destructor
   */
  ~Terrain();

  /** \brief _textureId getter
   ** \return Terrain Texture id
   **   matching the one in the Resources Manager std::map
   */
  unsigned int getTextureId();

  /** \brief _textureId setter
   */
  void setTextureId(unsigned int texture_id);


private:
  e_terrains _terrain;
  unsigned int _textureId; ///< current Texture id
  ResourcesManager *_rm; ///< contains the Texture matching _textureId
};

#endif /* !TERRAIN_HH_ */
