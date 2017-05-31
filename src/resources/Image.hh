/**
 * \file
 * \date Apr 25, 2013
 * \author Zermingore
 */

#ifndef RESOURCES_IMAGE_HH_
# define RESOURCES_IMAGE_HH_

# include <string>
# include <memory>
# include <graphics/graphic_types.hh>
# include <common/using.hh>
# include <resources/Resource.hh>


namespace resources {

/**
 * \class Image
 * \brief Image type, Derived from Resource
 */
class Image: public Resource
{
public:
  /**
   * \brief Image default Constructor
   */
  Image() = default;

  /**
   * \brief Image Constructor
   * \param file_name Image complete file name
   *   (with full path and extension)
   * \param name Image alias name
   *
   * set _texture to nullptr
   * _loaded to false
   */
  Image(const std::string file_name, const std::string name);

  /// Default destructor
  ~Image() = default;


  /**
   * \brief initializes _texture
   *   set _loaded to true
   */
  void initTexture();

  /**
   * \brief initializes _sprite
   *   set _loaded to true
   */
  void initSprite();

  /**
   * \brief _texture getter
   * loads the texture (and set _loaded flag) if _loaded was false
   * \return _texture
   */
  std::shared_ptr<graphics::Texture> getTexture();

  /**
   * \brief _sprite getter
   * loads the texture if needed (through initTexture)
   * allocates _sprites if needed (through initSprite)
   */
  std::shared_ptr<graphics::Sprite> sprite();


  /**
   * \brief set _sprite position
   * \param position: _sprite vector position
   */
  void setPosition(const Coords position);

  /**
   * \brief set _sprite position
   * \param position: _sprite vector position components
   */
  void setPosition(const graphics::component x, const graphics::component y);


  /**
   * \brief Set _rectangle and _sprite size.
   * \note The new size of the object depends on the cell size
   */
  void setSize(const graphics::Size2 size);

  /**
   * \brief set _rectangle and _sprite size
   * \param width: image width
   * \param height: image height
   */
  void setSize(const graphics::component width,
               const graphics::component height);


  /**
   * \brief set _rectangle and _sprite scale
   * \param scale new rectangle and sprite scale
   */
  void setScale(const graphics::Scale2 scale);

  /**
   * \brief set _rectangle and _sprite scale
   * \param width: image width
   * \param height: image height
   */
  void setScale(const graphics::component width,
                const graphics::component height);

  /**
   * \brief set _rectangle and _sprite scale using the same ratio
   * \param ratio: Scale ratio
   */
  void setScale(const float ratio);

  /**
   * \brief _fileName setter
   * \param file_name new image file name
   * \note Set _loaded to false
   */
  void setFileName(const std::string file_name);

  /**
   * \brief _sprite setter
   * \param sprite _sprite value
   */
  void setSprite(const std::shared_ptr<graphics::Sprite> sprite) {
    _sprite = sprite;
  }

  /**
   * \brief load Image texture to (V)RAM if necessary
   * \note Set _rectangle->texture to the new _texture
   * \return true if Image was loaded; false otherwise
   */
  bool load() override final;

  /**
   * \brief remove Image file from (V)RAM
   */
  void unload() override final;

  /**
   * \brief Reloads the texture (unload the previous one if any)
   */
  void reload(const std::string file_name);

  /**
   * \brief draws the Image in the cell coords.c, coords.l
   * \param c coordinate to display the image
   */
  void drawAtCell(const Coords c);

  /**
   * \brief draws the Image at _sprite's position
   */
  void draw();


private:
  std::shared_ptr<graphics::Texture> _texture;          ///< Texture data
  std::shared_ptr<graphics::Sprite> _sprite;            ///< Used to transform
  std::shared_ptr<graphics::RectangleShape> _rectangle; ///< image position
};


} // namespace resources



#endif /* !RESOURCES_IMAGE_HH_ */
