#ifndef TERRAIN_HH_
# define TERRAIN_HH_

# include <game/Cell.hh>
# include <resources/Image.hh>


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

  /** \brief Terrain Constructor
   **   builds a Terrain of type terrain
   */
  Terrain(e_terrains terrain);

  /** \brief Destructor
   */
  ~Terrain();

  /** \brief _imageName getter
   ** \return Image name (alias)
   */
  std::string getImageName();

  /** \brief _image getter
   */
  Image *getImage();


  /** \brief _image setter
   */
  void setTextureId(unsigned int texture_id);
  /** \brief _imageName setter
   */
  void setImageName(std::string image_name);


private:
  e_terrains _terrain; ///< terrain id matching e_types_terrain
  std::string _imageName; ///< image name (alias)
  Image* _image; ///< current Image
};

#endif /* !TERRAIN_HH_ */
