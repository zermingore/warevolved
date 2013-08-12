#ifndef TERRAIN_HH_
# define TERRAIN_HH_

# include <game/Cell.hh>
# include <resources/Image.hh>


// NOTE we could add a randomized sf::shape
//   (to dodge mosaic sad pattern)

/** \brief Terrain
 */
class Terrain
{
public:
  /** \brief Default Constructor
   */
  Terrain();

  /** \brief Terrain Constructor
   **   builds a Terrain of type terrain
   */
  explicit Terrain(e_terrain terrain);

  /** \brief Destructor
   */
  ~Terrain();

  /** \brief _imageName getter
   ** \return Image name (alias)
   */
  std::string getImageName();

  /** \brief _image getter
   ** \return Terrain's Image
   */
  Image *getImage();

  /** \brief _image setter
   */
  void setTextureId(unsigned int texture_id);

  /** \brief _imageName setter
   */
  void setImageName(std::string image_name);


private:
  e_terrain _terrain; ///< terrain id matching e_types_terrain
  std::string _imageName; ///< image name (alias)
  Image* _image; ///< current Image
};

#endif /* !TERRAIN_HH_ */
