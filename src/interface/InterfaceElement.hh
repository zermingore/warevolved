#ifndef INTERFACEELEMENT_HH_
# define INTERFACEELEMENT_HH_

/**
 * \file
 * \author Zermingore
 */

# include <string>
# include <memory>
# include <common/using.hh>
# include <common/structures/Vector.hh>
# include <interface/InterfaceSettings.hh>
# include <game/Map.hh>
# include <resources/ResourcesManager.hh>



namespace interface {

/**
 * \class InterfaceElement
 * \brief Represents an element of the interface (cursor, menu entry, ...).
 */
class InterfaceElement
{
public:
  /**
   * \brief Deleted default constructor as we need an image
   */
  InterfaceElement() = delete;

  /**
   * \brief constructor. Initialize position, scale and rotation of the element.
   * \param image_string name of the Image resource
   */
  explicit InterfaceElement(const std::string& image_name);


  // ___________________________ Getters / Setters _________________________ //
  /**
   * \brief image name getter.
   * \return name of the image resource.
   */
  std::string name() const { return _img_name; }

  /**
   * \brief position getter.
   * \return Position of the element in grid frame.
   */
  Coords position() const { return _position; }

  /**
   * \brief _coords getter
   * \return _coords value
   */
  Coords coords() { return _coords; }

  /**
   * \brief scale getter.
   * \return scale of the element, related to cells size.
   */
  Vector2<float> scale() const { return _scale; }

  /**
   * \brief rotation getter.
   * \return Rotation of the element in grid frame.
   */
  float rotation() const { return _rotation; }

  /**
   * \brief position setter.
   * \param position cells coordinates to place the element.
   */
  void setCoords(const Coords &coords) {
    _coords = coords;
  }

  /**
   * \brief position setter.
   * \param position cells coordinates to place the element.
   */
  void setPosition(const Coords &position) {
    _position = position;
  }

  /**
   * \brief scale setter.
   * \param scale_x scale in x related to cells size.
   * \param scale_y scale in y related to cells size.
   */
  void setScale(const float &scale_x, const float &scale_y)
  {
    _scale.x = scale_x;
    _scale.y = scale_y;
  }

  /**
   * \brief scale setter.
   * \param scale scale to apply in x and y related to cells size.
   */
  void setScale(const float &scale) { setScale(scale, scale); }

  /**
   * \brief rotation setter.
   *
   * The rotation angle is given in degrees.
   * The given rotation angle is related to the corner of the sprite.
   * The GraphicsEngine is in charge of the translation to have a rotation
   * related to che center of the sprite.
   *
   * \param rotation angle of the rotation.
   */
  void setRotation(const float &rotation) { _rotation = rotation; }


  std::shared_ptr<sf::Sprite> getSprite();


  /**
   * \brief Updates the graphical attributes of the elements before rendering
   */
  virtual void update(const std::shared_ptr<Map::MapGraphicsProperties> properties) = 0;



protected:
  std::string _img_name;   ///< Associated image name
  graphics::Image& _image; ///< Associated image
  Coords _position;        ///< Element position (in pixels)
  Coords _coords;          ///< Element position (in cells; not always filled)
  Vector2<float> _scale;   ///< Element scale (related to a Cell size)
  float _rotation;         ///< Element rotation
};

// InterfaceElementButton
//# include <resources/Font.hh>
//std::string _backgroundName; ///< background image name
//std::shared_ptr<sf::Text> _label; ///< label text
//Font _font; ///< label font


} // namespace interface

#endif /* !INTERFACEELEMENT_HH_ */
