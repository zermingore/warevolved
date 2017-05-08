/**
 * \file
 * \date Apr 25, 2013
 * \author Zermingore
 */

#ifndef RESOURCES_IMAGE_HH_
# define RESOURCES_IMAGE_HH_

# include <resources/Resource.hh>
# include <common/include.hh>
# include <common/using.hh>


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
   * sets _texture to NULL
   * _loaded to false
   */
  Image(const std::string file_name, const std::string name);

  /// Default destructor
  ~Image() = default;


  /**
   * \brief initializes _texture
   *   sets _loaded to true
   */
  void initTexture();

  /**
   * \brief initializes _sprite
   *   sets _loaded to true
   */
  void initSprite();

  /**
   * \brief _texture getter
   * loads the texture (and sets _loaded flag) if _loaded was false
   * \return _texture
   */
  std::shared_ptr<sf::Texture> getTexture();

  /**
   * \brief _sprite getter
   * loads the texture if needed (through initTexture)
   * allocates _sprites if needed (through initSprite)
   */
  std::shared_ptr<sf::Sprite> sprite();


  /**
   * \brief sets _sprite position
   * \param position: _sprite vector position
   */
  void setPosition(const Coords position);

  /**
   * \brief sets _sprite position
   * \param position: _sprite vector position components
   */
  void setPosition(const size_t x, const size_t y);


  /**
   * \brief sets _rectangle and _sprite size.
   *
   * The new size of the object depends on the cell size
   */
  void setSize(const sf::Vector2f size);

  /**
   * \brief sets _rectangle and _sprite size
   *   builds a sf::Vector2f
   * \param width: image width
   * \param height: image height
   */
  void setSize(const float width, const float height);


  /**
   * \brief sets _rectangle and _sprite scale
   */
  void setScale(const sf::Vector2f scale);

  /**
   * \brief sets _rectangle and _sprite scale
   *   builds a sf::Vector2f
   * \param width: image width
   * \param height: image height
   */
  void setScale(const float width, const float height);

  /**
   * \brief sets _rectangle and _sprite scale
   *   builds a sf::Vector2f to apply the ratio for the width and height
   * \param ratio: Scale ratio
   */
  void setScale(const float ratio);

  /**
   * \brief sets _fileName to file_name
   *   sets _loaded to false
   */
  void setFileName(const std::string file_name);

  /**
   * \brief _sprite setter
   * \param sprite _sprite value
   */
  void setSprite(const std::shared_ptr<sf::Sprite> sprite) { _sprite = sprite; }

  /**
   * \brief load Image texture to (V)RAM if necessary
   * sets _rectangle->texture to the new _texture
   *
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
  std::shared_ptr<sf::Texture> _texture; ///< texture data pointer
  std::shared_ptr<sf::Sprite> _sprite;   ///< Image sprite, for transformations
  std::shared_ptr<sf::RectangleShape> _rectangle; ///< image position
};


} // namespace resources



#endif /* !RESOURCES_IMAGE_HH_ */
