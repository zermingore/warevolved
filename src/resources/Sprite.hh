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
 * \class Sprite
 * \brief A Sprite is a Texture + a rectangle
 * \note Derived from Resource
 */
class Sprite: public Resource
{
public:
  /**
   * \brief Sprite default Constructor
   */
  Sprite() = default;

  /**
   * \brief Sprite Constructor
   * \param file_name Sprite complete file name
   *   (with full path and extension)
   * \param name Sprite alias name
   *
   * set _texture to nullptr
   * _loaded to false
   */
  Sprite(const std::string file_name, const std::string name);


  /**
   * \brief _texture getter
   * \return _texture
   */
  const auto getTexture() { return _texture; }

  /**
   * \brief _sprite getter
   */
  const auto sprite() { return _sprite; }


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
   * \param width: sprite width
   * \param height: sprite height
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
   * \param width: sprite width
   * \param height: sprite height
   */
  void setScale(const graphics::component width,
                const graphics::component height);

  /**
   * \brief set _rectangle and _sprite scale using the same ratio
   * \param ratio: Scale ratio
   */
  void setScale(const float ratio);

  /**
   * \brief set the Sprite 'global' Color
   * \param color Color to set
   */
  void setColor(const graphics::Color& color);

  /**
   * \brief _sprite setter
   * \param sprite _sprite value
   */
  void setSprite(const std::shared_ptr<graphics::Sprite> sprite) {
    _sprite = sprite;
  }

  /**
   * \brief draws the Sprite in the cell coords.c, coords.l
   * \param c coordinate to display the sprite
   */
  void drawAtCell(const Coords c);

  /**
   * \brief draws the Sprite at _sprite's position
   */
  void draw();


private:
  std::shared_ptr<graphics::Texture> _texture;          ///< Texture data
  std::shared_ptr<graphics::Sprite> _sprite;            ///< Used to transform
  std::shared_ptr<graphics::RectangleShape> _rectangle; ///< sprite position
};


} // namespace resources



#endif /* !RESOURCES_SPRITE_HH_ */
