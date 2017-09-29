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
   * \brief Deleted default Constructor
   */
  Sprite() = delete;

  /**
   * \brief Sprite Constructor
   * \param file_name Sprite complete file name
   *   (with full path and extension)
   */
  Sprite(const std::string file_name);

  /**
   * \brief Sprite Constructor, using an already loaded Texture
   * \param texture Pointer on an already loaded Texture to use
   */
  Sprite(const std::shared_ptr<graphics::Texture> texture);


  /**
   * \brief _texture getter
   * \return _texture
   */
  const auto getTexture() const { return _texture; }

  /**
   * \brief _sprite getter
   */
  const auto sprite() const { return _sprite; }


  /**
   * \brief _position getter
   */
  graphics::Pos2 const position();

  /**
   * \brief set _sprite position
   * \param position: _sprite vector position
   */
  void setPosition(const Coords position);

  /**
   * \brief set _sprite position
   * \param position: _sprite vector position
   */
  void setPosition(const graphics::Pos2 position);

  /**
   * \brief set _sprite position from 2 components
   * \param c column, x component of the sprite position
   * \param l line, y component of the sprite position
   */
  template<typename T>
  void setPosition(const T c, const T l)
  {
    _sprite->setPosition({ static_cast<graphics::component> (c),
                           static_cast<graphics::component> (l) });
  }


  /**
   * \brief Returns the size of the sprite
   */
  graphics::Size2 const size();

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
  template <typename T>
  void setSize(const T width, const T height)
  {
    graphics::Size2 size(_texture->getSize());
    _rectangle->setSize({ width, height });
    _sprite->setScale({ width / size.x, height / size.y });
  }


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
  template <typename T>
  void setScale(const T width, const T height)
  {
    _rectangle->setScale({ width, height });
    _sprite->setScale({ width, height });
  }


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
