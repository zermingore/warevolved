#ifndef IMAGE_HH_
# define IMAGE_HH_

# include <resources/Resource.hh>
# include <common/include.hh>


class Image : public Resource
{
public:
  Image();
  ~Image();

  bool load();
  bool unload();


private:
  sf::Texture* _texture;

  unsigned int _x; ///< image width
  unsigned int _y; ///< image height
};

#endif /* !IMAGE_HH_ */
