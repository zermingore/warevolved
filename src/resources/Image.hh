#ifndef IMAGE_HH_
# define IMAGE_HH_

# include <resources/Resource.hh>
# include <common/include.hh>


/** \brief Image Resource type
 ** Derived from Resource
 */

class Image : public Resource
{
public:
  Image();
  Image(const std::string file_name, std::string name, unsigned int id);

  ~Image();

  bool load();
  bool unload();


private:
  sf::Texture* _texture;

  unsigned int _x; ///< image width
  unsigned int _y; ///< image height
};

#endif /* !IMAGE_HH_ */
