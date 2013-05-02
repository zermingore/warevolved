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
  /** \brief Image default Constructor
   ** \deprecated you should always create a new image with an image file
   */
  Image();

  /** \brief Image Constructor
   ** \param file_name Image complete file name
   **   (with full path and extension)
   ** \param name Image alias name
   ** \param id Image unique identifier
   **
   ** sets _texture to NULL
   ** _loaded to false
   */
  Image(const std::string file_name,
		const std::string name,
		unsigned int id);

  /** \brief Destructor
   ** deletes the texture
   */
  ~Image();

  /** \brief _texture getter
   ** loads the texture (and sets _loaded flag) if _loaded was false
   ** \return _texture
   */
  sf::Texture *getTexture();

  /** \brief sets _fileName to file_name
   **   sets _loaded to false
   */
  void setFileName(std::string file_name);

  /** \brief load Image texture to (V)RAM if necessary
   ** sets _rectangle->texture to the new _texture
   **
   ** \return true if Image was loaded; false otherwise
   */
  bool load();

  /** \brief remove Image file from (V)RAM
   */
  void unload();

  /** \brief Reloads the texture (unload the previous one if any)
   */
  void reload(std::string file_name);


  /** \brief draws the Image designed by image_name at coordinates x, y
   ** \param pos_x x coordinate to display the image (in px)
   ** \param pos_y y coordinate to display the image (in px)
   ** \param width image width
   ** \param height image height
   */
  void draw(unsigned int pos_x, unsigned int pos_y,
			unsigned int width, unsigned int height);


private:
  sf::Texture *_texture; ///< texture data pointer
  sf::RectangleShape *_rectangle;
  unsigned int _width; ///< image width
  unsigned int _height; ///< image height
};

#endif /* !IMAGE_HH_ */
